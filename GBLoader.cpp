#include "GBLoader.h"
#include "gb.h" //In lab, we included this because we implemented several Y86 funcs in here.
//Note to us: we may not even need half of this stuff; GB roms are already compiled to binary so itt we will just do a dumb unload into ram at 0x0150 (until mappers).
bool gb::load(char* filename){
    return false;
}

static bool isValidFileName(std::string){
    return false;
}

static bool checkLine(std::string){
    return false;
}

static bool hasValidAddress(std::string){
    return false;
}

static bool hasData(std::string){
    return false;
}

static bool hasValidData(std::string){
    return false;
}

static std::string getAddress(std::string){
    return "";
}

static std::string getData(std::string){
    return "";
}

static bool checkHex(std::string){
    return false;
}

static uint8_t stringToHex(std::string){
    return 0;
}
