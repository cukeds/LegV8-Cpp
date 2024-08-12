//
// Created by Juan on 8/10/2024.
//

#include "ProgramCounter.h"
#include <iostream>
ProgramCounter::ProgramCounter() {
    pc = 0;
}

void ProgramCounter::increment() {
    pc += 4;
}

void ProgramCounter::setPC(int64_t pc) {
    this->pc = pc;
}

int64_t ProgramCounter::getPC() const {
    return pc;
}

void ProgramCounter::reset() {
    pc = 0;
}

void ProgramCounter::print() const {
    //std::cout << "PC: " << pc << "\n";
}

ProgramCounter::~ProgramCounter() {
    //std::cout << "ProgramCounter destructor called" << "\n";
}
