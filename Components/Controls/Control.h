//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_CONTROL_H
#define ARM_CONTROL_H

#include "Signal.h"
#include <utility>
#include <vector>
#include <cstdint>
#include <iostream>

using std::vector;

template<typename Opcode, typename Signals>
class Control {
protected:
    Signals signals;
public:

    Control(): signals(){
    };

    void setControlSignals(const Signals& _signals) {
        signals = std::move(_signals);
    }

    [[nodiscard]] const Signals& getControlSignals() {
        return signals;
    }
    void print() {
        for (const auto& signal : signals) {
            //std::cout << signal << "\n";
        }
    }

    virtual void decode(uint16_t&, Opcode&) = 0;

    ~Control(){
    }

};

#endif  //ARM_CONTROL_H

