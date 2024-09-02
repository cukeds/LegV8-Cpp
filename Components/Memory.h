#ifndef ARM_MEMORY_H
#define ARM_MEMORY_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <iomanip>

using std::uint64_t, std::uint8_t, std::uint32_t;
using std::vector;

class Memory {
private:
    vector<uint8_t> data;
public:
    explicit Memory(uint64_t size) : data(size, 0) {
        for(uint8_t & i : data) {
            i = 0;
        }
    }

    void write64(uint64_t address, uint64_t value) {
        // big endian
        for(int i = 0; i < 8; i++) {
            data[address + i] = (value >> (8 * (7 - i))) & 0xFF;
        }
        //std::cout<<"Writing to address: 0x"<<std::hex<<address<<" value: 0x"<<value<<"\n";

    }

    void write32(uint64_t address, uint32_t value) {
        // big endian
        for(int i = 0; i < 4; i++) {
            data[address + i] = (value >> (8 * (3 - i))) & 0xFF;
        }
    }

    void write16(uint64_t address, uint16_t value) {
        // big endian
        for(int i = 0; i < 2; i++) {
            data[address + i] = (value >> (8 * (1 - i))) & 0xFF;
        }

    }

    void write8(uint64_t address, uint8_t value) {
        data[address] = value;
    }


    [[nodiscard]] uint64_t read64(uint64_t address) const {
        uint64_t value = 0;
        // big endian
        for(int i = 0; i < 8; i++) {
            value |= (data[address + i] << (8 * (7 - i)));
        }
        return value;
    }

    [[nodiscard]] uint32_t read32(uint64_t address) const {
        // big endian
        uint32_t value = 0;
        for(int i = 0; i < 4; i++) {
            value |= (data[address + i] << (8 * (3 - i)));
        }
        return value;
    }

    [[nodiscard]] uint16_t read16(uint64_t address) const {
        // big endian
        uint16_t value = 0;
        for(int i = 0; i < 2; i++) {
            value |= (data[address + i] << (8 * (1 - i)));
        }
        return value;
    }

    [[nodiscard]] uint8_t read8(uint64_t address) const {
        return data[address];
    }


    void reset() {
        for (uint8_t & i : data) {
            i = 0;
        }
    }

    void print(bool instructions) const {
        //std::cout << std::hex;
        int s = 16;
        if (instructions) {
            s = 8;
        }
        for (size_t i = 0; i < data.size(); i+=4) {
            //std::cout << "Address: 0x"  << std::setw(16) << std::setfill('0') << i;
            uint64_t value = read64(i);
            //std::cout << " Value: 0x" << std::setw(s) << std::setfill('0') << value << "\n";
        }
        //std::cout << std::dec;
    }

    void print(uint64_t address, bool instructions) const {
        int s = 16;
        if (instructions) {
            s = 8;
        }
        //std::cout << std::hex;


        //std::cout << "Address: 0x" << std::setw(16) << std::setfill('0') << std::hex << address
                  //<< " Value: 0x" << std::setw(s) << std::setfill('0') << (instructions ? read32(address) : read64(address)) << "\n";
        //std::cout << std::dec;
    }


    [[nodiscard]] int size () const {
        return data.size();
    }

    [[nodiscard]] const vector<uint8_t>& getData() {
        return data;
    }

    ~Memory() = default;
};

#endif //ARM_MEMORY_H
