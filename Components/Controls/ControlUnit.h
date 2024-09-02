//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_CONTROLUNIT_H
#define ARM_CONTROLUNIT_H
#include "Control.h"
#include "../Types.h"

class ControlUnit : public Control<uint16_t, ControlSignals>{

public:
    ControlUnit() : Control(), format(Format::None){
    }

private:
    Format format;
    void decode(uint16_t& opcode, uint16_t& opcode2) override{
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
            case 0x69b: {
                signals.Reg2Loc =  Signal::ZERO;      // Reg2Loc
                signals.ALUSrc =  Signal::ZERO;      // ALUSrc
                signals.MemtoReg =  Signal::ZERO;      // MemtoReg
                signals.RegWrite =  Signal::ONE;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::X;         // MemAccess1
                signals.MemAccess0 =  Signal::X;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ONE;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;      // EnableFlags



                format = Format::R;
            }
                break;
            case 0x750:
            case 0x558:
            case 0x758: {
                signals.Reg2Loc =  Signal::ZERO;      // Reg2Loc
                signals.ALUSrc =  Signal::ZERO;      // ALUSrc
                signals.MemtoReg =  Signal::ZERO;      // MemtoReg
                signals.RegWrite =  Signal::ONE;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::X;         // MemAccess1
                signals.MemAccess0 =  Signal::X;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ONE;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ONE;       // EnableFlags

                format = Format::R;
            }
                break;
                // I types
            case 0x488:
            case 0x489:
            case 0x490:
            case 0x491:
            case 0x590:
            case 0x591:
            case 0x688:
            case 0x689: {
                signals.Reg2Loc =  Signal::X;      // Reg2Loc
                signals.ALUSrc =  Signal::ONE;      // ALUSrc
                signals.MemtoReg =  Signal::X;      // MemtoReg
                signals.RegWrite =  Signal::ONE;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::X;         // MemAccess1
                signals.MemAccess0 =  Signal::X;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ONE;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;       // EnableFlags

                format = Format::I;
            }
                break;
            case 0x588:// flags
            case 0x589:// flags
            case 0x790:// flags
            case 0x791:// flags
            case 0x788:// flags
            case 0x789:// flags
            {
                signals.Reg2Loc =  Signal::X;      // Reg2Loc
                signals.ALUSrc =  Signal::ONE;      // ALUSrc
                signals.MemtoReg =  Signal::X;      // MemtoReg
                signals.RegWrite =  Signal::ONE;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::X;         // MemAccess1
                signals.MemAccess0 =  Signal::X;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ONE;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ONE;       // EnableFlags


                format = Format::I;
            }
                break;
            case 0x690:
            case 0x691:
            {
                format = Format::None;
                break;
            }
            // D types
            // LDUR
            case 0x7C2:
            {
                signals.Reg2Loc =  Signal::X;      // Reg2Loc
                signals.ALUSrc =  Signal::ONE;      // ALUSrc
                signals.MemtoReg =  Signal::ONE;      // MemtoReg
                signals.RegWrite =  Signal::ONE;       // RegWrite
                signals.MemRead =  Signal::ONE;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::ONE;         // MemAccess1
                signals.MemAccess0 =  Signal::ONE;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;       // EnableFlags


                format = Format::D;
                break;
            }
            // LDURB
            case 0x1C2:{
                signals.Reg2Loc =  Signal::X;      // Reg2Loc
                signals.ALUSrc =  Signal::ONE;      // ALUSrc
                signals.MemtoReg =  Signal::ONE;      // MemtoReg
                signals.RegWrite =  Signal::ONE;       // RegWrite
                signals.MemRead =  Signal::ONE;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::ZERO;         // MemAccess1
                signals.MemAccess0 =  Signal::ZERO;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;       // EnableFlags


                format = Format::D;
                break;
            }
            // LDURH
            case 0x3C2:
            {
                signals.Reg2Loc =  Signal::X;      // Reg2Loc
                signals.ALUSrc =  Signal::ONE;      // ALUSrc
                signals.MemtoReg =  Signal::ONE;      // MemtoReg
                signals.RegWrite =  Signal::ONE;       // RegWrite
                signals.MemRead =  Signal::ONE;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::ZERO;         // MemAccess1
                signals.MemAccess0 =  Signal::ONE;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;       // EnableFlags


                format = Format::D;
                break;
            }
            // STUR
            case 0x7C0:
            {
                signals.Reg2Loc =  Signal::ONE;      // Reg2Loc
                signals.ALUSrc =  Signal::ONE;      // ALUSrc
                signals.MemtoReg =  Signal::X;      // MemtoReg
                signals.RegWrite =  Signal::ZERO;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ONE;      // MemWrite
                signals.MemAccess1 =  Signal::ONE;         // MemAccess1
                signals.MemAccess0 =  Signal::ONE;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;       // EnableFlags


                format = Format::D;
            }
                break;
                // STURB
            case 0x1C0:{
                signals.Reg2Loc =  Signal::ONE;      // Reg2Loc
                signals.ALUSrc =  Signal::ONE;      // ALUSrc
                signals.MemtoReg =  Signal::X;      // MemtoReg
                signals.RegWrite =  Signal::ZERO;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ONE;      // MemWrite
                signals.MemAccess1 =  Signal::ZERO;         // MemAccess1
                signals.MemAccess0 =  Signal::ZERO;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;       // EnableFlags


                format = Format::D;
                break;
            }
            // STURH
            case 0x3C0:{
                signals.Reg2Loc =  Signal::ONE;      // Reg2Loc
                signals.ALUSrc =  Signal::ONE;      // ALUSrc
                signals.MemtoReg =  Signal::X;      // MemtoReg
                signals.RegWrite =  Signal::ZERO;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ONE;      // MemWrite
                signals.MemAccess1 =  Signal::ZERO;         // MemAccess1
                signals.MemAccess0 =  Signal::ONE;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;       // EnableFlags


                format = Format::D;
                break;
            }
            // STURW
            case 0x5C0:{
                signals.Reg2Loc =  Signal::ONE;      // Reg2Loc
                signals.ALUSrc =  Signal::ONE;      // ALUSrc
                signals.MemtoReg =  Signal::X;      // MemtoReg
                signals.RegWrite =  Signal::ZERO;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ONE;      // MemWrite
                signals.MemAccess1 =  Signal::ONE;         // MemAccess1
                signals.MemAccess0 =  Signal::ZERO;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;       // EnableFlags


                format = Format::D;
                break;
            }
            // B types
            case 0x0A0: {
                signals.Reg2Loc =  Signal::X;      // Reg2Loc
                signals.ALUSrc =  Signal::X;      // ALUSrc
                signals.MemtoReg =  Signal::X;      // MemtoReg
                signals.RegWrite =  Signal::ZERO;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::X;         // MemAccess1
                signals.MemAccess0 =  Signal::X;         // MemAccess0
                signals.BranchCondition1 =  Signal::ONE;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ONE;      // BranchCondition0
                signals.ALUOp1 = Signal::X;       // ALUOp1
                signals.ALUOp0 = Signal::X;      // ALUOp0
                signals.EnableFlags = Signal::X;       // EnableFlags


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
                signals.Reg2Loc =  Signal::ONE;      // Reg2Loc
                signals.ALUSrc =  Signal::ZERO;      // ALUSrc
                signals.MemtoReg =  Signal::X;      // MemtoReg
                signals.RegWrite =  Signal::ZERO;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::X;         // MemAccess1
                signals.MemAccess0 =  Signal::X;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ONE;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ONE;      // ALUOp0
                signals.EnableFlags = Signal::ONE;       // EnableFlags


                format = Format::CB;
            }
                break;
                // CBNZ
            case 0x5A8:
            {
                signals.Reg2Loc =  Signal::ONE;      // Reg2Loc
                signals.ALUSrc =  Signal::ZERO;      // ALUSrc
                signals.MemtoReg =  Signal::X;      // MemtoReg
                signals.RegWrite =  Signal::ZERO;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::X;         // MemAccess1
                signals.MemAccess0 =  Signal::X;         // MemAccess0
                signals.BranchCondition1 =  Signal::ONE;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ONE;      // ALUOp0
                signals.EnableFlags = Signal::ONE;       // EnableFlags


                format = Format::CB;
            }
                break;
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
                signals.Reg2Loc =  Signal::ZERO;      // Reg2Loc
                signals.ALUSrc =  Signal::ZERO;      // ALUSrc
                signals.MemtoReg =  Signal::ZERO;      // MemtoReg
                signals.RegWrite =  Signal::ZERO;       // RegWrite
                signals.MemRead =  Signal::ZERO;      // MemRead
                signals.MemWrite =  Signal::ZERO;      // MemWrite
                signals.MemAccess1 =  Signal::X;         // MemAccess1
                signals.MemAccess0 =  Signal::X;         // MemAccess0
                signals.BranchCondition1 =  Signal::ZERO;      // BranchCondition1
                signals.BranchCondition0 =  Signal::ZERO;      // BranchCondition0
                signals.ALUOp1 = Signal::ZERO;       // ALUOp1
                signals.ALUOp0 = Signal::ZERO;      // ALUOp0
                signals.EnableFlags = Signal::ZERO;       // EnableFlags
               
                format = Format::None;
        }

    }
public:
    void decode(uint16_t& opcode){
        decode(opcode, opcode);
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
