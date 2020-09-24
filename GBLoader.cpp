#include <fstream>
#include <cstdint>
#include <filesystem>
#include "Sim.h"
#include "gb.h" //In lab, we included this because we implemented several Y86 funcs in here.
//Note to us: we may not even need half of this stuff; GB roms are already compiled to binary so itt we will just do a dumb unload into ram at 0x0100 (until mappers).


/*
 * load
 * Sets our status to OK, then checks the filename. If the filename is valid, then we proceed to readFile.
 */
bool gb::load(std::string filename){
    bool status = true;
    status = std::filesystem::exists(filename);
    if(status) status = readFile(filename); 
    return status;
}

/*
 * readFile
 * Loads a file into Memory, by using successive calls to putByte().
 */
bool gb::readFile(std::string filename){
    bool status = true;
    std::ifstream file(filename, std::ios::binary);
    int baddy = CART_HEADER; // byte address will just begin at 0x0100.
    int len = (ROM_END - CART_HEADER);
    for(int i = 0; i <= len; i++){
        getMemory().putByte((baddy + i), file.get());
    }
    file.close();
    return status;
}
