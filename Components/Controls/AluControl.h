//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_ALUCONTROL_H
#define ARM_ALUCONTROL_H
#include "Control.h"

class AluControl : public Control<vector<Signal>> {
private:
    vector<Signal::Value> controlSignals;
public:
    AluControl() : Control() {
        controlSignals = {
            Signal::ZERO,   // b3
            Signal::ZERO,   // b2
            Signal::ZERO,   // b1
            Signal::ZERO    // b0
        };
        setControlSignals(controlSignals);
    }
    void decode(uint16_t* opcode, vector<Signal>* opcode2) override{
        if (opcode2->size() > 2){
            throw std::invalid_argument("Invalid opcode size");
        }

        // 00 ADD
        if ((*opcode2)[0].getValue() == Signal::ZERO && (*opcode2)[1].getValue() == Signal::ZERO){
            controlSignals[0] = Signal::ZERO;
            controlSignals[1] = Signal::ZERO;
            controlSignals[2] = Signal::ONE;
            controlSignals[3] = Signal::ZERO;
            setControlSignals(controlSignals);

        }
        // Pass B
        else if ((*opcode2)[1].getValue() == Signal::ONE){
            controlSignals[0] = Signal::ZERO;
            controlSignals[1] = Signal::ONE;
            controlSignals[2] = Signal::ONE;
            controlSignals[3] = Signal::ONE;
            setControlSignals(controlSignals);

            // depends on opcode
        } else if ((*opcode2)[0].getValue() == Signal::ONE) {
            // we need bits 0-10
            uint16_t bits = *opcode & 0x7FF;
            // R-types
            switch(bits){
                // ADD
                case 0x458:
                case 0x558:
                case 0x488:
                case 0x489:
                case 0x588:
                case 0x589:
                    controlSignals[0] = Signal::ZERO;
                    controlSignals[1] = Signal::ZERO;
                    controlSignals[2] = Signal::ONE;
                    controlSignals[3] = Signal::ZERO;
                    setControlSignals(controlSignals);
                    break;
                // SUB
                case 0x658:
                case 0x758:
                case 0x688:
                case 0x689:
                case 0x788:
                case 0x789:
                    controlSignals[0] = Signal::ZERO;
                    controlSignals[1] = Signal::ONE;
                    controlSignals[2] = Signal::ONE;
                    controlSignals[3] = Signal::ZERO;
                    setControlSignals(controlSignals);
                    break;
                //  AND
                case 0x450:
                case 0x750:
                case 0x490:
                case 0x491:
                case 0x790:
                case 0x791:
                    controlSignals[0] = Signal::ZERO;
                    controlSignals[1] = Signal::ZERO;
                    controlSignals[2] = Signal::ZERO;
                    controlSignals[3] = Signal::ZERO;
                    setControlSignals(controlSignals);
                    break;
                // ORR
                case 0x550:
                case 0x590:
                case 0x591:
                    controlSignals[0] = Signal::ZERO;
                    controlSignals[1] = Signal::ZERO;
                    controlSignals[2] = Signal::ZERO;
                    controlSignals[3] = Signal::ONE;
                    setControlSignals(controlSignals);
                    break;
                default:
                    std::cerr << "Invalid opcode" << "\n";
                    return;
            }

        }

    }
};


#endif //ARM_ALUCONTROL_H
