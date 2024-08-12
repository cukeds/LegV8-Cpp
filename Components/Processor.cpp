//
// Created by Juan on 8/10/2024.
//

#include "Processor.h"
#include <iostream>
#include <bitset>


Processor::Processor(int dataMemorySize,
                     int instructionMemorySize,
                     Display* display
) :
        pc(),
        registers(),
        dataMemory(dataMemorySize),
        instructionMemory(instructionMemorySize),
        controlUnit(),
        aluControlUnit(),
        alu(),
        signExtend() {
    controlSignals = vector<Signal>();
    currentInstruction = 0;
    opcode = 0;
    sign_extended_immediate = 0;
    aluControlSignals = vector<Signal>();
    aluFlags = vector<bool>();
    branchAddress = 0;
    this->display = display;
}

void Processor::setup(vector<uint32_t> machineCode) {

    for(int i = 0; i < machineCode.size(); i++) {
        instructionMemory.write32(i*4, machineCode[i]);
        instructionMemory.print(i*4, true);
    }

    registers.setRegister(0x002, display->width*display->height); // Matrix size
    registers.setRegister(0x003, 0x4); // 4
    registers.setRegister(0x005, 0x1148114811481148); // Color
    registers.setRegister(0x006, 0x0);  // Address


    for(int i = 0; i < dataMemory.size()-1; i+=2){
        dataMemory.write16(i, uint16_t(0x1bba));
        display->setPixel( (i/2)%display->width, (i/2)/display->height, (uint16_t)0x1bba);
    }
}

void Processor::process() {
    if (!InstructionFetch()) {
        pc.increment();
        return;
    }


    auto regBank = InstructionDecode();


    branchAddress = (sign_extended_immediate << 2);

    uint64_t rn = regBank[0];
    uint64_t rm = regBank[1];
    uint8_t rd_address = regBank[2];
    uint64_t result;

    if (controlSignals[ControlUnit::ControlSignal::ALUSrc].getValue()) {
        result = Execute(rn, sign_extended_immediate);
    } else {
        result = Execute(rn, rm);
    }


    uint64_t mem_access_result = 0;
    if(controlSignals[ControlUnit::ControlSignal::MemWrite].getValue() || controlSignals[ControlUnit::ControlSignal::MemRead].getValue())
    {
        if(!controlSignals[ControlUnit::ControlSignal::MemAccess0].getValue() && !controlSignals[ControlUnit::ControlSignal::MemAccess1].getValue()) {
            mem_access_result = MemoryAccess(result, rm, 8);
        }
        else if(controlSignals[ControlUnit::ControlSignal::MemAccess0].getValue() && !controlSignals[ControlUnit::ControlSignal::MemAccess1].getValue()) {
            mem_access_result = MemoryAccess(result, rm, 16);
        }
        else if(!controlSignals[ControlUnit::ControlSignal::MemAccess0].getValue() && controlSignals[ControlUnit::ControlSignal::MemAccess1].getValue()) {
            mem_access_result = MemoryAccess(result, rm, 32);
        }
        else{
            mem_access_result = MemoryAccess(result, rm);
        }
    }


    //std::cout<< "Mem Access Result: 0x" << std::hex << std::setw(16) << std::setfill('0') << mem_access_result << std::dec << "\n";

    if (controlSignals[ControlUnit::ControlSignal::MemtoReg].getValue()) {
        result = mem_access_result;
    }

    WriteBack(rd_address, result);


}

bool Processor::InstructionFetch() {

    if ((pc.getPC() / 4) >= instructionMemory.size()) {
        //std::cout << "End of program" << "\n";
        throw std::runtime_error("End of program");
    }

    currentInstruction = instructionMemory.read32(pc.getPC());


//    instructionMemory.print(pc.getPC(), true);

    return currentInstruction != 0;
}

vector<uint64_t> Processor::InstructionDecode() {

    // Opcode = currentInstruction[31:21]
    opcode = (currentInstruction >> 21) & 0x7FF;
    //std::cout << "Opcode: 0x" << std::hex << std::setw(8) << std::setfill('0') << opcode << std::dec << "\n";
    controlUnit.decode(opcode);
    controlSignals = controlUnit.getControlSignals();
    controlUnit.print();

    sign_extended_immediate = signExtend.sign_extend(currentInstruction, controlUnit.getFormat());
    //std::cout << "Sign extended: 0x" << std::hex << std::setw(16) << std::setfill('0') << sign_extended_immediate << "\n";

    uint8_t rd_address = currentInstruction & 0x1F; // rt in D and CB format
    uint8_t rn_address = (currentInstruction >> 5) & 0x1F; // NOT USED IN CB FORMAT
    uint8_t rm_address;

    if (controlSignals[ControlUnit::ControlSignal::Reg2Loc].getValue()) {
        rm_address = rd_address;
    } else {
        rm_address = (currentInstruction >> 16) & 0x1F; // ONLY R format
    }

    // print addresses

    //std::cout << "&Rd: " << std::hex << std::setw(2) << std::setfill('0') << (int) rd_address << std::dec << "\n";
    //std::cout << "&Rn: " << std::hex << std::setw(2) << std::setfill('0') << (int) rn_address << std::dec << "\n";
    //std::cout << "&Rm: " << std::hex << std::setw(2) << std::setfill('0') << (int) rm_address << std::dec << "\n";

    uint64_t rn = registers[rn_address];
    uint64_t rm = registers[rm_address];

    //std::cout << "Rn: " << std::hex << std::setw(16) << std::setfill('0') << rn << std::dec << "\n";
    //std::cout << "Rm: " << std::hex << std::setw(16) << std::setfill('0') << rm << std::dec << "\n";
    return {rn, rm, rd_address};
}


uint64_t Processor::Execute(uint64_t rn, uint64_t rm) {
    aluControlUnit.decode(opcode, {controlSignals[ControlUnit::ControlSignal::ALUOp1],
                                   controlSignals[ControlUnit::ControlSignal::ALUOp0]});
    // aluControlUnit.getControlSignals is of the form {b3, b2, b1, b0}
    aluControlSignals = aluControlUnit.getControlSignals();


    uint8_t aluControl = 0;
    for (int i = 0; i < 4; i++) {
        aluControl |= aluControlSignals[i].getValue() << (3 - i);
    }
    std::bitset<4> aluControlBits(aluControl);
    //std::cout << "Alu Control: 0b" << aluControlBits << "\n";
    auto result = alu.execute(rn, rm, aluControl, controlSignals[ControlUnit::ControlSignal::EnableFlags].getValue());
    //std::cout << "Alu Result: 0x" << std::hex << std::setw(16) << std::setfill('0') << result << std::dec << "\n";
    aluFlags = alu.getflags();
    return result;
}

uint64_t Processor::MemoryAccess(uint64_t address, uint64_t writeData, int size) {
    if(address >= dataMemory.size()){
        throw std::runtime_error("Memory Access out of bounds");
    }

    uint8_t writeData8 = writeData & 0xFF;
    uint16_t writeData16 = writeData & 0xFFFF;
    uint32_t writeData32 = writeData & 0xFFFFFFFF;
    switch(size){
        case 8:
            writeData = writeData8;
            break;
        case 16:
            writeData = writeData16;
            break;
        case 32:
            writeData = writeData32;
            break;
        case 64:
            break;
        default:
            throw std::runtime_error("Invalid size");
    }


    if(address < display->width*display->height*2 && controlSignals[ControlUnit::ControlSignal::MemWrite].getValue())
    {
        //std::cout<<"Writing to display"<<"\n";
        uint16_t pixel;
        uint16_t pixelMagic;
        int temp_address = address;
        for(int i = 0; i<size/16; i++) {
            // 1234 1234 1234 1238
            pixel = (writeData >> (16 * i)) & 0xFFFF;
            pixelMagic = writeData & 0xFFFF;
            display->setPixel((int)(temp_address)%display->width, (int)(temp_address)/display->height, pixelMagic);
            temp_address++;
        }
    }


    //std::cout << "Memory Access" << "\n";
    if (controlSignals[ControlUnit::ControlSignal::MemRead].getValue()) {
        //std::cout << "Reading from memory" << "\n";
        switch(size){
            case 8:
                return dataMemory.read8(address);
            case 16:
                return dataMemory.read16(address);
            case 32:
                return dataMemory.read32(address);
        }
        return dataMemory.read64(address);
    } else if (controlSignals[ControlUnit::ControlSignal::MemWrite].getValue()) {
        //std::cout << "Writing to memory" << "\n";
        switch(size){
            case 8:
                dataMemory.write8(address, writeData);
                return dataMemory.read8(address);
            case 16:
                dataMemory.write16(address, writeData);
                return dataMemory.read16(address);
            case 32:
                dataMemory.write32(address, writeData);
                return dataMemory.read32(address);
        }
        dataMemory.write64(address, writeData);
        return dataMemory.read64(address);
    } else {
        return 0;
    }
}

void Processor::WriteBack(uint8_t reg, uint64_t data) {
    if (controlSignals[ControlUnit::ControlSignal::RegWrite].getValue()) {
        registers.setRegister(reg, data);
    }

    if (checkBranch()) {
        //std::cout << "Branching to 0x" << std::hex << std::setw(16) << std::setfill('0') << (pc.getPC() + branchAddress) << std::dec << "\n";
        pc.setPC(pc.getPC() + branchAddress);
    }else
    {
        pc.increment();
    }
}

bool Processor::checkBranch() {
    //std::cout<< "Checking branch" << "\n";
    if (controlSignals.empty()) {
        //std::cout<< "Control signals empty" << "\n";
        return false;
    }
    bool branch;
    // CBZ
    branch = !controlSignals[ControlUnit::ControlSignal::BranchCondition1].getValue() && controlSignals[ControlUnit::ControlSignal::BranchCondition0].getValue();
    if (branch) {
        //std::cout<< "CBZ" << "\n";
        return alu.getflags()[ALU::FLAGS::Zero];
    }
    // CBNZ
    branch = controlSignals[ControlUnit::ControlSignal::BranchCondition1].getValue() && !controlSignals[ControlUnit::ControlSignal::BranchCondition0].getValue();
    if(branch){
        //std::cout<< "CBNZ" << "\n";
        return !alu.getflags()[ALU::FLAGS::Zero];
    }
    branch = controlSignals[ControlUnit::ControlSignal::BranchCondition1].getValue() && controlSignals[ControlUnit::ControlSignal::BranchCondition0].getValue();
    // B
    if(branch){
        //std::cout<< "B" << "\n";
        return true;
    }
    return false;
}

void Processor::reset(bool resetMemory) {
    pc.reset();
    if (resetMemory) {
        dataMemory.reset();
        instructionMemory.reset();
    }
}

void Processor::print() {
    pc.print();
}

Memory Processor::getDataMemory() {

    return dataMemory;
}

Processor::~Processor() {
    //std::cout << "Processor destructor called" << "\n";
}

