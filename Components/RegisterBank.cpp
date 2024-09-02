//
// Created by Juan on 8/10/2024.
//

#include "RegisterBank.h"

RegisterBank::RegisterBank() : registers(32, 0) {
}

void RegisterBank::setRegister(uint8_t _register, uint64_t data) {
    if(_register > 31) {
        throw std::invalid_argument("Invalid register number");
    }
    if(_register == 31){
        return;
    }
    registers[_register] = data;
}

void RegisterBank::print() {
    for(int i = 0; i < 32; i++) {
        //std::cout << "Register " << i << ": 0x";
        //std::cout << std::hex << std::setw(16) << std::setfill('0') << registers[i] << "\n";
        //std::cout << std::dec;
    }
}

void RegisterBank::print(uint8_t _register) {
//    if(_register > 31) {
//        throw std::invalid_argument("Invalid register number");
//    }
    //std::cout << "Register " << _register << ": 0x";
    //std::cout << std::hex << std::setw(16) << std::setfill('0') << registers[_register] << "\n";
    //std::cout << std::dec;
}

RegisterBank::~RegisterBank() {
    registers.clear();
}
