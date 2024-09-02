//
// Created by Juan on 8/11/2024.
//

#ifndef ARM_TYPES_H
#define ARM_TYPES_H

#define PIXEL_SIZE 2
#include "./Controls/Signal.h"
enum class Format{
    None = 0,
    R = 1,
    I = 2,
    D = 3,
    B = 4,
    CB = 5,
    IM = 6
};

struct ControlSignals{
    Signal Reg2Loc;
    Signal ALUSrc;
    Signal MemtoReg;
    Signal RegWrite;
    Signal MemRead;
    Signal MemWrite;
    Signal MemAccess1;
    Signal MemAccess0;
    Signal BranchCondition1;
    Signal BranchCondition0;
    Signal ALUOp1;
    Signal ALUOp0;
    Signal EnableFlags;
};

struct AluSignals{
    Signal b3;
    Signal b2;
    Signal b1;
    Signal b0;
};

struct DecodedRegisters{
    uint64_t Rn;
    uint64_t Rm;
    uint64_t Rd;
};

struct DisplaySize{
    int width;
    int height;
};
#endif //ARM_TYPES_H
