// PPUnit.cpp
// Authors: Hunter King, Joe Story

#include <iostream>
#include <iomanip>
#include "Sim.h"
#include "PPUnit.h" 

void PPUnit::addMem(Memory * arg_memory){
    memory = arg_memory;
}

/*
 * getRowColor
 * Given two bytes, returns a pointer to an array of 8 PPUnits on screen with their associated color value (0-3).
 * For example, the tile 0x5030 will return: [0, 1, 2, 3, 0, 0, 0, 0]
 */
uint32_t * PPUnit::getRowColor(uint16_t row){
    uint16_t byte1 = (row & 0xFF00) >> 8; // grab high order byte out of the 2
    uint16_t byte2 = (row & 0x00FF);      // grab low order byte
    uint16_t mask = 0x01;

    std::cout << "our tile is: 0x" << std::hex << row << std::endl;
    std::cout << "our byte1 is: 0x" << std::hex << byte1 << std::endl;
    std::cout << "our byte2 is: 0x" << std::hex << byte2 << std::endl;

    for (int i = 0; i < 8; i++){
            if (byte1 & (mask << i)) miniPix[7-i] += 1; // if byte 1's bit is on
            if (byte2 & (mask << i)) miniPix[7-i] += 2; // if byte 2's bit is on
    }
    
    uint32_t * final_color;
    
    for (int i = 0; i < 4; i++){
        switch (i)
        {
        case 0:
            final_color[i] = COLOR0;
            break;

        case 1:
            final_color[i] = COLOR1;
            break;

        case 2:
            final_color[i] = COLOR2;
            break;

        case 3:
            final_color[i] = COLOR3;
            break;

        default:
            break;
        }
    }
    return final_color;
}

/*
 * scan_line()
 * render one scan line.
 */
void PPUnit::scan_line(){
    uint8_t control = memory->getByte(LCD_CONTROL);
    uint8_t test = 1;
    if(control & (test << BG_DISPLAY)) render_tiles();
    //if(control & (test << OBJ_DISPLAY)) render_sprites;
}

void PPUnit::render_tiles(){
// where to draw the visual area and the window
   uint8_t scrollY = memory->getByte(SCROLL_Y);
   uint8_t scrollX = memory->getByte(SCROLL_X);
   uint8_t windowY = memory->getByte(WINDOW_Y);
   uint8_t windowX = memory->getByte(WINDOW_X) - 7;
//    printf("ScrollY: %02x\n", memory->getByte(SCROLL_Y));
    uint8_t positionY = 0; // used to calculate current scanline
    uint8_t positionX = 0; // used in pixel writing loop
    uint16_t tileData = 0;
    uint16_t bgData = 0;
    bool is_unsigned = true;
    bool inWindow = false;

    // if the window is enabled
    if (WIN_DISPLAY_ENABLE){
        // if the current scanline is within the windows y-position
        if (windowY <= LY){
            // then we are using the window
            inWindow = true;
        }
    }

    // this block finds which tile data we are using
    if (GB_WINDOW_SELECT) tileData = VRAM; // VRAM is 0x8000
    else{
        // this bit tells what range and if it is signed or not
        tileData = 0x8000; 
        is_unsigned = false;
    }

    // this block finds which background data we are using
    if (inWindow){
        positionY = LY + scrollY; // if we are in the window set current bounds, if we are outside fix it
        if (BG_MAP_SELECT) bgData = 0x9C00;
        else bgData = 0x9800;
    }
    else {
        positionY = LY - windowY;
    }


   // find which of the 8 tile scanlines we are on
   uint16_t tileRow = (((uint16_t) (positionY/8))*32);

   // draw 160 pixels on this scanline
   for (int i = 0; i < 160; i++){
        positionX = i + scrollX;
        // translate the current positionX to window space if necessary
        if (inWindow && i >= windowX) positionX = i - windowX;

        // which tile does the positionX fall within
        uint16_t tileCol = positionX / 8;
        int16_t tileNum;
        uint16_t tileAddress = bgData + tileRow + tileCol;
        // what tile are we in, either signed or unsigned
        //FIXME: not sure if we need the cast on the unsigned
        if (is_unsigned) tileNum = (uint8_t) memory->getByte(tileAddress);
        else tileNum = (int8_t) memory->getByte(tileAddress);

        // find where this tile id is memory
        uint16_t tileLocation = tileData;
        if (is_unsigned) tileLocation += (tileNum * 16);
        else tileLocation += ((tileNum + 128) * 16);

        // find what vertical line of the tile we are on
        // this is to get correct tile data
        // FIXME: from here on out we use our own sdl and so on to find color and write pixels onto the screen

        uint8_t line = (positionY  % 8) * 2; // each line of data takes 2 bytes
        uint8_t data1 = memory->getByte(tileLocation + line);
        uint8_t data2 = memory->getByte(tileLocation + line + 1);
        uint16_t data = (data1 << 8) + data2;
        if (i % 20 == 0) lcdArray[i] = *getRowColor(data);
   }


}