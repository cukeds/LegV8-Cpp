//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_CONTROLUNIT_H
#define ARM_CONTROLUNIT_H
#include "Control.h"
#include "../Types.h"

class ControlUnit : public Control<int>{

private:
    Format format;

    void decode(uint16_t opcode, int opcode2) override{
        // Decoding according to the opcode
        if(opcode >= 0x0A0 && opcode <= 0x0BF) opcode = 0x0A0; //B
        else if(opcode >= 0x4A0 && opcode <= 0x4BF) opcode = 0x4A0; // BL
        else if(opcode >= 0x5A8 && opcode <= 0x5AF) opcode = 0x5A8; // CBNZ
        else if(opcode >= 0x5A0 && opcode <= 0x5A7) opcode = 0x5A0; // CBZ
        else if(opcode >= 0x2A0 && opcode <= 0x2A7) opcode = 0x2A0; // B.cond
        else if(opcode >= 0x794 && opcode <= 0x797) opcode = 0x794; // MOVK
        else if(opcode >= 0x694 && opcode <= 0x697) opcode = 0x694; // MOVZ

        switch(opcode) {
            // R types
            case 0x450:
            case 0x458:
            case 0x550:
            case 0x658:
            case 0x650:
            case 0x69a:
            case 0x69b:{
                setControlSignals({
                  Signal("Reg2Loc", Signal::ZERO),
                  Signal("ALUSrc", Signal::ZERO),
                  Signal("MemtoReg", Signal::ZERO),
                  Signal("RegWrite", Signal::ONE),
                  Signal("MemRead", Signal::ZERO),
                  Signal("MemWrite", Signal::ZERO),
                  Signal("MemAccess1", Signal::X),
                  Signal("MemAccess0",Signal::X),
                  Signal("BranchCondition1", Signal::ZERO),
                  Signal("BranchCondition0", Signal::ZERO),
                  Signal("ALUOp1", Signal::ONE),
                  Signal("ALUOp0", Signal::ZERO),
                  Signal("EnableFlags", Signal::ZERO)
                });
                format = Format::R;
                break;
            }
            case 0x750:
            case 0x558:
            case 0x758: {
                setControlSignals({
                  Signal("Reg2Loc", Signal::ZERO),
                  Signal("ALUSrc", Signal::ZERO),
                  Signal("MemtoReg", Signal::ZERO),
                  Signal("RegWrite", Signal::ONE),
                  Signal("MemRead", Signal::ZERO),
                  Signal("MemWrite", Signal::ZERO),
                  Signal("MemAccess1", Signal::X),
                  Signal("MemAccess0",Signal::X),
                  Signal("BranchCondition1", Signal::ZERO),
                  Signal("BranchCondition0", Signal::ZERO),
                  Signal("ALUOp1", Signal::ONE),
                  Signal("ALUOp0", Signal::ZERO),
                  Signal("EnableFlags", Signal::ONE)
                  });
                format = Format::R;
                break;
            }
            // I types
            case 0x488:
            case 0x489:
            case 0x588:
            case 0x589:
            case 0x490:
            case 0x491:
            case 0x790:
            case 0x791:
            case 0x690:
            case 0x691:
            case 0x590:
            case 0x591:
            case 0x688:
            case 0x689:
            case 0x788:
            case 0x789:
                // TODO
                format = Format::I;
                break;
            // D types
            // LDUR
            case 0x7C2:
            {
                setControlSignals({
                      Signal("Reg2Loc", Signal::X),
                      Signal("ALUSrc", Signal::ONE),
                      Signal("MemtoReg", Signal::ONE),
                      Signal("RegWrite", Signal::ONE),
                      Signal("MemRead", Signal::ONE),
                      Signal("MemWrite", Signal::ZERO),
                      Signal("MemAccess1", Signal::ONE),
                      Signal("MemAccess0",Signal::ONE),
                      Signal("BranchCondition1", Signal::ZERO),
                      Signal("BranchCondition0", Signal::ZERO),
                      Signal("ALUOp1", Signal::ZERO),
                      Signal("ALUOp0", Signal::ZERO),
                      Signal("EnableFlags", Signal::ZERO)
                  });
                format = Format::D;
                break;
            }
            // LDURB
            case 0x1C2:
            {
                setControlSignals({
                  Signal("Reg2Loc", Signal::X),
                  Signal("ALUSrc", Signal::ONE),
                  Signal("MemtoReg", Signal::ONE),
                  Signal("RegWrite", Signal::ONE),
                  Signal("MemRead", Signal::ONE),
                  Signal("MemWrite", Signal::ZERO),
                  Signal("MemAccess1", Signal::ZERO),
                  Signal("MemAccess0",Signal::ZERO),
                  Signal("BranchCondition1", Signal::ZERO),
                  Signal("BranchCondition0", Signal::ZERO),
                  Signal("ALUOp1", Signal::ZERO),
                  Signal("ALUOp0", Signal::ZERO),
                  Signal("EnableFlags", Signal::ZERO)
                  });
                format = Format::D;
                break;
            }
            // LDURH
            case 0x3C2:
            {
                setControlSignals({
                      Signal("Reg2Loc", Signal::X),
                      Signal("ALUSrc", Signal::ONE),
                      Signal("MemtoReg", Signal::ONE),
                      Signal("RegWrite", Signal::ONE),
                      Signal("MemRead", Signal::ONE),
                      Signal("MemWrite", Signal::ZERO),
                      Signal("MemAccess1", Signal::ZERO),
                      Signal("MemAccess0",Signal::ONE),
                      Signal("BranchCondition1", Signal::ZERO),
                      Signal("BranchCondition0", Signal::ZERO),
                      Signal("ALUOp1", Signal::ZERO),
                      Signal("ALUOp0", Signal::ZERO),
                      Signal("EnableFlags", Signal::ZERO)
                  });
                format = Format::D;
                break;
            }
            // STUR
            case 0x7C0:
            {
                setControlSignals({
                  Signal("Reg2Loc", Signal::ONE),
                  Signal("ALUSrc", Signal::ONE),
                  Signal("MemtoReg", Signal::X),
                  Signal("RegWrite", Signal::ZERO),
                  Signal("MemRead", Signal::ZERO),
                  Signal("MemWrite", Signal::ONE),
                  Signal("MemAccess1", Signal::ONE),
                  Signal("MemAccess0",Signal::ONE),
                  Signal("BranchCondition1", Signal::ZERO),
                  Signal("BranchCondition0", Signal::ZERO),
                  Signal("ALUOp1", Signal::ZERO),
                  Signal("ALUOp0", Signal::ZERO),
                  Signal("EnableFlags", Signal::ZERO)
                  });
                format = Format::D;
                break;
            }
            // STURB
            case 0x1C0:{
                setControlSignals({
                  Signal("Reg2Loc", Signal::ONE),
                  Signal("ALUSrc", Signal::ONE),
                  Signal("MemtoReg", Signal::X),
                  Signal("RegWrite", Signal::ZERO),
                  Signal("MemRead", Signal::ZERO),
                  Signal("MemWrite", Signal::ONE),
                  Signal("MemAccess1", Signal::ZERO),
                  Signal("MemAccess0",Signal::ZERO),
                  Signal("BranchCondition1", Signal::ZERO),
                  Signal("BranchCondition0", Signal::ZERO),
                  Signal("ALUOp1", Signal::ZERO),
                  Signal("ALUOp0", Signal::ZERO),
                  Signal("EnableFlags", Signal::ZERO)
                  });
                format = Format::D;
                break;
            }
            // STURH
            case 0x3C0:{
                setControlSignals({
                  Signal("Reg2Loc", Signal::ONE),
                  Signal("ALUSrc", Signal::ONE),
                  Signal("MemtoReg", Signal::X),
                  Signal("RegWrite", Signal::ZERO),
                  Signal("MemRead", Signal::ZERO),
                  Signal("MemWrite", Signal::ONE),
                  Signal("MemAccess1", Signal::ZERO),
                  Signal("MemAccess0",Signal::ONE),
                  Signal("BranchCondition1", Signal::ZERO),
                  Signal("BranchCondition0", Signal::ZERO),
                  Signal("ALUOp1", Signal::ZERO),
                  Signal("ALUOp0", Signal::ZERO),
                  Signal("EnableFlags", Signal::ZERO)
                  });
                format = Format::D;
                break;
            }
            // STURW
            case 0x5C0:{
                setControlSignals({
                  Signal("Reg2Loc", Signal::ONE),
                  Signal("ALUSrc", Signal::ONE),
                  Signal("MemtoReg", Signal::X),
                  Signal("RegWrite", Signal::ZERO),
                  Signal("MemRead", Signal::ZERO),
                  Signal("MemWrite", Signal::ONE),
                  Signal("MemAccess1", Signal::ONE),
                  Signal("MemAccess0",Signal::ZERO),
                  Signal("BranchCondition1", Signal::ZERO),
                  Signal("BranchCondition0", Signal::ZERO),
                  Signal("ALUOp1", Signal::ZERO),
                  Signal("ALUOp0", Signal::ZERO),
                  Signal("EnableFlags", Signal::ZERO)
                  });
                format = Format::D;
                break;
            }
            // B types
            case 0x0A0: {
                setControlSignals({
                  Signal("Reg2Loc", Signal::X),
                  Signal("ALUSrc", Signal::X),
                  Signal("MemtoReg", Signal::X),
                  Signal("RegWrite", Signal::ZERO),
                  Signal("MemRead", Signal::ZERO),
                  Signal("MemWrite", Signal::ZERO),
                  Signal("MemAccess1", Signal::X),
                  Signal("MemAccess0",Signal::X),
                  Signal("BranchCondition1", Signal::ONE),
                  Signal("BranchCondition0", Signal::ONE),
                  Signal("ALUOp1", Signal::X),
                  Signal("ALUOp0", Signal::X),
                  Signal("EnableFlags", Signal::X)
                  });
                format = Format::B;
                break;
            }
            case 0x4A0:
                format = Format::B;
                break;
            // CB types
            // CBZ
            case 0x5A0:
            {
                setControlSignals({
                  Signal("Reg2Loc", Signal::ONE),
                  Signal("ALUSrc", Signal::ZERO),
                  Signal("MemtoReg", Signal::X),
                  Signal("RegWrite", Signal::ZERO),
                  Signal("MemRead", Signal::ZERO),
                  Signal("MemWrite", Signal::ZERO),
                  Signal("MemAccess1", Signal::X),
                  Signal("MemAccess0",Signal::X),
                  Signal("BranchCondition1", Signal::ZERO),
                  Signal("BranchCondition0", Signal::ONE),
                  Signal("ALUOp1", Signal::ZERO),
                  Signal("ALUOp0", Signal::ONE),
                  Signal("EnableFlags", Signal::ONE)
                  });
                format = Format::CB;
                break;
            }
            // CBNZ
            case 0x5A8:
            {
                setControlSignals({
                  Signal("Reg2Loc", Signal::ONE),
                  Signal("ALUSrc", Signal::ZERO),
                  Signal("MemtoReg", Signal::X),
                  Signal("RegWrite", Signal::ZERO),
                  Signal("MemRead", Signal::ZERO),
                  Signal("MemWrite", Signal::ZERO),
                  Signal("MemAccess1", Signal::X),
                  Signal("MemAccess0",Signal::X),
                  Signal("BranchCondition1", Signal::ONE),
                  Signal("BranchCondition0", Signal::ZERO),
                  Signal("ALUOp1", Signal::ZERO),
                  Signal("ALUOp0", Signal::ONE),
                  Signal("EnableFlags", Signal::ONE)
                  });
                format = Format::CB;
                break;
            }
            // IM types
            // MOVK
            case 0x794:
                format = Format::IM;
                break;
            // MOVZ
            case 0x694:
                format = Format::IM;
                break;
            default:
                setControlSignals({
              Signal("Reg2Loc", Signal::ZERO),
              Signal("ALUSrc", Signal::ZERO),
              Signal("MemtoReg", Signal::ZERO),
              Signal("RegWrite", Signal::ZERO),
              Signal("MemRead", Signal::ZERO),
              Signal("MemWrite", Signal::ZERO),
              Signal("MemAccess1", Signal::X),
              Signal("MemAccess0",Signal::X),
              Signal("BranchCondition1", Signal::ZERO),
              Signal("BranchCondition0", Signal::ZERO),
              Signal("ALUOp1", Signal::ZERO),
              Signal("ALUOp0", Signal::ZERO),
              Signal("EnableFlags", Signal::ZERO)
              });
        }
    }
public:
    void decode(uint16_t opcode){
        decode(opcode, 0);
    }

    Format getFormat() {
        return format;
    }

    enum ControlSignal{
        Reg2Loc,
        ALUSrc,
        MemtoReg,
        RegWrite,
        MemRead,
        MemWrite,
        MemAccess1,
        MemAccess0,
        BranchCondition1,
        BranchCondition0,
        ALUOp1,
        ALUOp0,
        EnableFlags
    };
};


#endif //ARM_CONTROLUNIT_H
