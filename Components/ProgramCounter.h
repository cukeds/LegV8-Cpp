//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_PROGRAMCOUNTER_H
#define ARM_PROGRAMCOUNTER_H
#include <cstdint>

using std::uint64_t;

class ProgramCounter {
private:
    int64_t pc;
public:
    ProgramCounter();
    void increment();
    void setPC(int64_t _pc);
    [[nodiscard]] int64_t getPC() const;
    void reset();
    void print() const;
    ~ProgramCounter();
};


#endif //ARM_PROGRAMCOUNTER_H
