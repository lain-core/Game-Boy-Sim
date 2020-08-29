#include "GBLoader.h"
#include "gb.h" //In lab, we included this because we implemented several Y86 funcs in here.
//Note to us: we may not even need half of this stuff; GB roms are already compiled to binary so itt we will just do a dumb unload into ram at 0x0150 (until mappers).
bool gb::load(char* filename){
    return false;
}

namespace GBLoader{

static bool isValidFileName(std::string filename){
    bool validName = true;

    //If filename is empty, return false.
    if(filename.length() == 0){
        std::cout << "Filename was empty." << std::endl;
        validName = false;
    }
    //If file extension is wrong, return false.
    else{
        filename = filename.substr(filename.find('.'), filename.length());
        if(filename != ".gb" || filename != ".GB") validName = false;
    }
    return validName;
}

static bool checkLine(std::string instruction){
    //Check that line will buff.
    bool willBuff = true;
    willBuff = willBuff && hasValidAddress(instruction);
    willBuff = willBuff && hasData(instruction);
    willBuff = willBuff && hasValidData(instruction);
    
    return willBuff;
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

} //end namespace Y86Loader
