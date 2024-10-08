//
// Created by Juan on 8/10/2024.
//
#ifndef ARM_ALU_H
#define ARM_ALU_H

#include <vector>
#include <iostream>
#include <cstdint>

using std::vector;
using std::uint64_t;
class ALU {
public:
    enum class FLAGS {
        Negative = 0,
        Zero = 1,
        Carry = 2,
        Overflow = 3
    };

    ALU(): result(0) {
        flags = vector<bool>(4, false);
    };

private:
    vector<bool> flags;
    uint64_t result;

    void setFlags(bool N, bool Z, bool C, bool V) {
        flags[(int)FLAGS::Negative] = N;
        flags[(int)FLAGS::Zero] = Z;
        flags[(int)FLAGS::Carry] = C;
        flags[(int)FLAGS::Overflow] = V;

    }

    uint64_t add(uint64_t a, uint64_t b, bool enableFlags=false) {
        result = a + b;

        if(enableFlags){
            bool Na = a & 0x8000000000000000;
            bool Nb = b & 0x8000000000000000;
            bool Nr = result & 0x8000000000000000;
            setFlags(Nr, result == 0, result < a || result < b, (Na && Nb && !Nr) || (!Na && !Nb && Nr));
        }
        return result;
    }

    uint64_t sub(uint64_t a, uint64_t b, bool enableFlags=false) {
        result = a - b;

        if(enableFlags){
            bool Na = a & 0x8000000000000000;
            bool Nb = b & 0x8000000000000000;
            bool Nr = result & 0x8000000000000000;
            setFlags(Nr, result == 0, a < b, (Na && !Nb && !Nr) || (!Na && Nb && Nr));
        }
        return result;
    }

    uint64_t and_(uint64_t a, uint64_t b, bool enableFlags=false) {
        result = a & b;
        if(enableFlags){
            setFlags(result & 0x8000000000000000, result == 0, false, false);
        }
        return result;
    }

    uint64_t or_(uint64_t a, uint64_t b, bool enableFlags=false) {
        result = a | b;
        if(enableFlags){
            setFlags(result & 0x8000000000000000, result == 0, false, false);
        }
        return result;
    }

    uint64_t xor_(uint64_t a, uint64_t b, bool enableFlags=false) {
        result = a ^ b;
        if(enableFlags){
            setFlags(result & 0x8000000000000000, result == 0, false, false);
        }
        return result;
    }

    uint64_t lsl(uint64_t a, uint64_t b, bool enableFlags=false) {
        result = a << b;
        if(enableFlags){
            setFlags(result & 0x8000000000000000, result == 0, false, false);
        }
        return result;
    }

    uint64_t lsr(uint64_t a, uint64_t b, bool enableFlags=false) {
        result = a >> b;
        if(enableFlags){
            setFlags(result & 0x8000000000000000, result == 0, false, false);
        }
        return result;
    }

    // Pass B and set flags
    uint64_t passthroughb(uint64_t a, uint64_t b, bool enableFlags=false) {
        result = b;
        if(enableFlags){
            setFlags(result & 0x8000000000000000, result == 0, false, false);
        }
        return result;
    }

    uint64_t nor(uint64_t a, uint64_t b, bool enableFlags=false) {
        result = ~(a | b);
        if(enableFlags){
            setFlags(result & 0x8000000000000000, result == 0, false, false);
        }
        return result;
    }

    void print() const {

        //std::cout << std::hex;
        //std::cout << "Result: 0x" << std::setw(16) << std::setfill('0') << result << "\n";
        //std::cout << std::dec;
    }

public:


    uint64_t execute(uint64_t a, uint64_t b, uint8_t aluControl, bool enableFlags=false) {
        switch(aluControl) {
            case 0b0000:
                return and_(a, b, enableFlags);
            case 0b0001:
                return or_(a, b, enableFlags);
            case 0b0010:
                return add(a, b, enableFlags);
            case 0b0110:
                return sub(a, b, enableFlags);
            case 0b0111:
                return passthroughb(a, b, enableFlags);
            case 0b1100:
                return nor(a, b, enableFlags);
            default:
                throw std::invalid_argument("Invalid Execute control signal");
        }

    }

    vector<bool>* getflags(){
        return &flags;
    }


    ~ALU()= default;
};


#endif //ARM_ALU_H
