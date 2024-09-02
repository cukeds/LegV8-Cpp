//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_ALUCONTROL_H
#define ARM_ALUCONTROL_H
#include "Control.h"

class AluControl : public Control<vector<Signal>, AluSignals> {
public:
    AluControl() : Control() {
        
    }
    void decode(uint16_t& opcode, vector<Signal>& opcode2) override{
        if (opcode2.size() > 2){
            throw std::invalid_argument("Invalid opcode size");
        }

        // 00 ADD
        if (opcode2[0].getValue() == Signal::ZERO && opcode2[1].getValue() == Signal::ZERO){
            signals.b3 = Signal::ZERO;
            signals.b2 = Signal::ZERO;
            signals.b1 = Signal::ONE;
            signals.b0 = Signal::ZERO;
        }
        // Pass B
        else if (opcode2[1].getValue() == Signal::ONE){
            signals.b3 = Signal::ZERO;
            signals.b2 = Signal::ONE;
            signals.b1 = Signal::ONE;
            signals.b0 = Signal::ONE;
            

            // depends on opcode
        } else if (opcode2[0].getValue() == Signal::ONE) {
            // we need bits 0-10
            uint16_t bits = opcode & 0x7FF;
            // R-types
            switch(bits){
                // ADD
                case 0x458:
                case 0x558:
                case 0x488:
                case 0x489:
                case 0x588:
                case 0x589:
                    signals.b3 = Signal::ZERO;
                    signals.b2 = Signal::ZERO;
                    signals.b1 = Signal::ONE;
                    signals.b0 = Signal::ZERO;
                    
                    break;
                // SUB
                case 0x658:
                case 0x758:
                case 0x688:
                case 0x689:
                case 0x788:
                case 0x789:
                    signals.b3 = Signal::ZERO;
                    signals.b2 = Signal::ONE;
                    signals.b1 = Signal::ONE;
                    signals.b0 = Signal::ZERO;
                    
                    break;
                //  AND
                case 0x450:
                case 0x750:
                case 0x490:
                case 0x491:
                case 0x790:
                case 0x791:
                    signals.b3 = Signal::ZERO;
                    signals.b2 = Signal::ZERO;
                    signals.b1 = Signal::ZERO;
                    signals.b0 = Signal::ZERO;
                    
                    break;
                // ORR
                case 0x550:
                case 0x590:
                case 0x591:
                    signals.b3 = Signal::ZERO;
                    signals.b2 = Signal::ZERO;
                    signals.b1 = Signal::ZERO;
                    signals.b0 = Signal::ONE;
                    
                    break;
                default:
                    std::cerr << "Invalid opcode" << "\n";
                    return;
            }

        }

    }
};


#endif //ARM_ALUCONTROL_H
