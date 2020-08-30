#include "GBLoader.h"
#include "Sim.h"
#include "gb.h" //In lab, we included this because we implemented several Y86 funcs in here.
//Note to us: we may not even need half of this stuff; GB roms are already compiled to binary so itt we will just do a dumb unload into ram at 0x0150 (until mappers).
bool gb::load(char* filename){
    bool status = true;
    //status = GBLoader::isValidFileName(filename);
    if(status) status = readFile(filename); 
    return status;
}

bool gb::readFile(std::string filename){
    std::cout << "in readfile!" << std::endl;
    bool status = true;
    //std::ifstream file = malloc(32000);
    std::ifstream file(filename, std::ios::binary);
    int baddy = ROM_START; // byte address will just begin at 0x0150 because thats where a cart rom starts
    int len = (ROM_END - ROM_START);
    /*for(int i = 0; i < len; i++){
        getMemory().putByte((baddy + i), file.get());
    }*/
    std::cout << "closing file.." << std::endl;
    file.close();
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


} //end namespace Y86Loader
