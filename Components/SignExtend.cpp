//
// Created by Juan on 8/10/2024.
//

#include <stdexcept>
#include "SignExtend.h"


SignExtend::SignExtend() = default;

SignExtend::~SignExtend() = default;

uint64_t SignExtend::sign_extend(const uint32_t& instruction, const Format& format) {
    // Sign extend the instruction
    // Determine the instruction type, extract the immediate value, and sign extend it
    uint64_t sign_extended = 0;
    switch(format){
        case Format::None:
        case Format::R:
            break;
        case Format::I:
            sign_extended = (instruction >> 10) & 0xFFF;
            break;

        case Format::D:
            sign_extended = (instruction >> 12) & 0x1FF;
            if (sign_extended & (1 << 8)) {
                sign_extended |= 0xFFFFFFFFFFFFFE00;
            }
            break;

        case Format::B:
            sign_extended = (instruction) & 0x3FFFFFF;
            if (sign_extended & (1 << 25)) {
                sign_extended |= 0xFFFFFFFFFC000000;
            }
            break;

        case Format::CB:
            sign_extended = (instruction >> 5) & 0x7FFFF;
            if (sign_extended & (1 << 18)) {
                sign_extended |= 0xFFFFFFFFFFF80000;
            }
            break;
        case Format::IM:
            sign_extended = (instruction >> 5) & 0xFFFF;
            break;
        default:
            throw std::invalid_argument("Invalid instruction format");
    }
    return sign_extended;
}
