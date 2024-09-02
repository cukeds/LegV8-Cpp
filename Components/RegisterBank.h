//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_REGISTERBANK_H
#define ARM_REGISTERBANK_H
#include <cstdint>
#include <vector>
#include <iostream>

using std::uint64_t;
using std::uint8_t;
using std::vector;


class RegisterBank {
private:
    vector<uint64_t> registers;
public:
    RegisterBank();
    void setRegister(uint8_t, uint64_t);
    [[nodiscard]] inline const uint64_t getRegister(const uint8_t& _register){
        if(_register > 31) {
            throw std::invalid_argument("Invalid register number");
        }
        if(_register == 31){
            return 0;
        }
        return registers[_register];
    };
    void print();
    void print(uint8_t);
    ~RegisterBank();

    inline uint64_t& operator[](uint8_t index) {
        return registers[index];
    }

    inline const uint64_t& operator[](uint8_t index) const {
        return registers[index];
    }
};


#endif //ARM_REGISTERBANK_H
