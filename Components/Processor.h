//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_PROCESSOR_H
#define ARM_PROCESSOR_H

#include "ProgramCounter.h"
#include "Memory.h"
#include "RegisterBank.h"
#include "Controls/ControlUnit.h"
#include "Controls/AluControl.h"
#include "ALU.h"
#include "SignExtend.h"
#include "../Display/Display.h"
#include <unordered_map>
#include "Types.h"

class Processor {
private:
    ProgramCounter pc;
    Memory dataMemory;
    Memory instructionMemory;
    RegisterBank registers;
    ControlUnit controlUnit;
    AluControl aluControlUnit;
    ALU alu;
    SignExtend signExtend;
    DisplaySize display;

    vector<Signal> controlSignals;
    uint32_t currentInstruction;
    uint16_t opcode;
    uint64_t sign_extended_immediate;
    vector<Signal> aluControlSignals;
    vector<Signal> opcode2;
    int64_t branchAddress;
    DecodedRegisters decodedRegisters;

    bool InstructionFetch();
    void InstructionDecode();
    uint64_t Execute(uint64_t, uint64_t);
    uint64_t MemoryAccess(uint64_t, uint64_t = 0, int size = 64);
    void WriteBack(uint8_t, uint64_t);
    bool checkBranch();
public:
    Processor(int, int, DisplaySize);
    void process();
    void reset(bool resetMemory = false);
    void print();
    void setup(vector<uint32_t>);
    const vector<uint8_t>& getDataMemory();
    ~Processor();



};


#endif //ARM_PROCESSOR_H
