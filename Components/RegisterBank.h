//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_REGISTERBANK_H
#define ARM_REGISTERBANK_H
#include <cstdint>
#include <vector>

using std::uint64_t;
using std::uint8_t;
using std::vector;


class RegisterBank {
private:
    vector<uint64_t> registers;
public:
    RegisterBank();
    void setRegister(uint8_t, uint64_t);
    uint64_t getRegister(uint8_t);
    void print();
    void print(uint8_t);
    ~RegisterBank();

    uint64_t& operator[](uint8_t index) {
        return registers[index];
    }

    const uint64_t& operator[](uint8_t index) const {
        return registers[index];
    }
};


#endif //ARM_REGISTERBANK_H
