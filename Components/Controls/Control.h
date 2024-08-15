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

template<typename Opcode>
class Control {
protected:
    vector<Signal> signals;
public:

    Control(): signals(vector<Signal>()){
        signals.reserve(32);
    };
    void setControlSignals(vector<Signal> _signals) {
        signals = std::move(_signals);
    }
    void setControlSignals(vector<Signal::Value> _signals) {
        for (int i = 0; i < _signals.size(); i++) {
            signals[i].setValue(_signals[i]);
        }
    }
    vector<Signal>* getControlSignals() {
        return &signals;
    }
    void print() {
        for (const auto& signal : signals) {
            //std::cout << signal << "\n";
        }
    }

    virtual void decode(uint16_t*, Opcode*) = 0;

    ~Control(){
        signals.clear();
    }

};

#endif  //ARM_CONTROL_H

