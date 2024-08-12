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
    std::string name;
    Value value;

public:
    Signal(std::string  _name, Value _value);
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] Value getValue() const;
    void setValue(Value newValue);

    friend std::ostream& operator<<(std::ostream& os, const Signal& signal) {
        os << signal.name << ": " << signal.value;
        return os;
    }
};

#endif //ARM_SIGNAL_H
