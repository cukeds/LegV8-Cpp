#include "Signal.h"

#include <utility>

Signal::Signal(std::string  _name, Value _value)
        : name(std::move(_name)), value(_value) {
}

std::string Signal::getName() const {
    return name;
}

Signal::Value Signal::getValue() const {
    return value == Signal::ONE ? Signal::ONE : Signal::ZERO;
}

void Signal::setValue(Value newValue) {
    value = newValue;
}
