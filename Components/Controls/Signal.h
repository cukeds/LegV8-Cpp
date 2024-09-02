#ifndef ARM_SIGNAL_H
#define ARM_SIGNAL_H

#include <iostream>
#include <string>

class Signal {
public:
    // Enumeration for signal values
    enum Value {
        ZERO = 0,
        ONE = 1,
        X = 2
    };

private:
    Value value;

public:
    Signal() : value(Signal::X){};
    explicit Signal(Value _value) : value(){};
    [[nodiscard]] inline Value getValue() const{
        return value == Signal::ONE ? Signal::ONE : Signal::ZERO;
    };

    inline Signal& operator=(const Signal::Value& sValue){
        value = sValue;
        return *this;
    };


};

#endif //ARM_SIGNAL_H
