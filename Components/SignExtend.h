//
// Created by Juan on 8/10/2024.
//

#ifndef ARM_SIGNEXTEND_H
#define ARM_SIGNEXTEND_H

#include <cstdint>
#include "Types.h"

using std::uint32_t, std::uint64_t;
class SignExtend {
public:
    SignExtend();
    ~SignExtend();

    uint64_t sign_extend(uint32_t instruction, Format format);
};


#endif //ARM_SIGNEXTEND_H
