#include "../gb.h"

//CALL n16 *** BIG DEAL
void gb::call(uint16_t address){

}
//CALL cc,n16
void gb::call_cc(bool flag, uint16_t address){

}
//JP HL
void gb::jp_hl(){

}
//JP n16
void gb::jp(uint16_t){

}
//JP cc,n16 *** BIG DEAL
void gb::jp_cc(bool flag, uint16_t address){

}
//JR e8     *** BIG DEAL
void gb::jr(uint8_t value){

}
//JR cc,e8
void gb::jr_cc(bool flag, uint8_t value){

}
//RET cc
void gb::ret_cc(bool flag){

}
//RET       *** BIG DEAL
void gb::ret(){

}
//RETI
void gb::reti(){

}
//RST vec
void gb::vec(uint8_t vec){
    
}