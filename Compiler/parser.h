//
// Created by Juan on 8/11/2024.
//
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdint>
#include <iostream>
#include <unordered_map>

enum class InstructionFormat { R, I, D, B, CB, IM };

struct Instruction {
    std::string mnemonic;
    InstructionFormat format;
    uint32_t opcode;
    uint32_t opcodeRange;
};

const std::unordered_map<std::string, Instruction> instructionSet = {
        {"AND",	{ "AND",InstructionFormat::R, 0x450, 0}},
        {"ADD", { "ADD",InstructionFormat::R, 0x458, 0}},
        {"ORR", { "ORR",InstructionFormat::R, 0x550, 0}},
        {"SUB", { "SUB",InstructionFormat::R, 0x658, 0}},
        {"XOR", { "XOR",InstructionFormat::R, 0x650, 0}},
        {"LSR", { "LSR",InstructionFormat::R, 0x69a, 0}},
        {"LSL", { "LSL",InstructionFormat::R, 0x69b, 0}},
        {"ANDS", {"ANDS",InstructionFormat::R, 0x750, 0}},
        {"ADDS", {"ADDS",InstructionFormat::R, 0x558, 0}},
        {"SUBS", {"SUBS",InstructionFormat::R, 0x758, 0}},
        {"ADDI", { "ADDI", InstructionFormat::I, 0x488, 1}},
        {"ADDIS", { "ADDIS", InstructionFormat::I, 0x588, 1}},
        {"ANDI", { "ANDI", InstructionFormat::I, 0x490, 1}},
        {"ANDIS", { "ANDIS", InstructionFormat::I, 0x790, 1}},
        {"XORI", { "XORI", InstructionFormat::I, 0x690, 1}},
        {"ORRI", { "ORRI", InstructionFormat::I, 0x590, 1}},
        {"SUBI", { "SUBI", InstructionFormat::I, 0x688, 1}},
        {"SUBIS", { "SUBIS", InstructionFormat::I, 0x788, 1}},
        {"LDUR", {"LDUR", InstructionFormat::D, 0x7C2, 0}},
        {"LDURB", {"LDURB", InstructionFormat::D, 0x1C2, 0}},
        {"LDURH", {"LDURH", InstructionFormat::D, 0x3C2, 0}},
        {"STUR", {"STUR", InstructionFormat::D, 0x7C0, 0}},
        {"STURB", {"STURB", InstructionFormat::D, 0x1C0, 0}},
        {"STURH", {"STURH", InstructionFormat::D, 0x3C0, 0}},
        {"STURW", {"STURW", InstructionFormat::D, 0x5C0, 0}},
        {"B", {"B", InstructionFormat::B, 0x0A0, 5}},
        {"BL", {"BL", InstructionFormat::B, 0x4A0, 5}},
        {"CBNZ", {"CBNZ", InstructionFormat::CB, 0x5A8, 3}},
        {"CBZ", {"CBZ", InstructionFormat::CB, 0x5A0, 3}},
        {"B.cond", {"B.cond", InstructionFormat::CB, 0x2A0, 3}},
        {"MOVK", {"MOVK", InstructionFormat::IM, 0x794, 2}},
        {"MOVZ", {"MOVZ", InstructionFormat::IM, 0x694, 2}}
};


struct RInstruction {
    uint32_t opcode : 11;
    uint32_t Rm : 5;
    uint32_t shamt : 6;
    uint32_t Rn : 5;
    uint32_t Rd : 5;
};

struct IInstruction {
    uint32_t opcode : 10;
    uint32_t imm : 12;
    uint32_t Rt : 5;
    uint32_t Rn : 5;
};

struct DInstruction {
    uint32_t opcode : 11;
    uint32_t addr : 9;
    uint32_t op2 : 2;
    uint32_t Rn : 5;
    uint32_t Rt : 5;
};


struct CBInstruction {
    uint32_t opcode : 8;
    uint32_t Rt : 5;
    int32_t imm : 19;
};


struct BInstruction {
    uint32_t opcode : 6;
    uint32_t imm : 26;
};

struct IMInstruction {
    uint32_t opcode : 9;
    uint32_t lsl : 2;
    uint32_t imm : 16;
    uint32_t Rd : 5;
};


std::vector<std::string> tokenize(const std::string& line) {
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(ss, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}

uint32_t getRegisterNumber(const std::string& reg) {
    // Convert register name to register number.
    // Example: "R0" -> 0, "R1" -> 1, etc.
    if(reg.substr(1)=="ZR") return 31;
    return std::stoi(reg.substr(1));
}

uint32_t calculateOpcode(const std::string& mnemonic) {
    return instructionSet.at(mnemonic).opcode >> instructionSet.at(mnemonic).opcodeRange;
}

uint32_t encodeRInstruction(std::vector<std::string>& tokens) {
    // Extract fields (opcode, Rn, Rd, etc.) and convert to binary format.
    // Assume register names are parsed elsewhere.
    RInstruction instr;
    instr.opcode = calculateOpcode(tokens[0]);

    instr.Rd = getRegisterNumber(tokens[1]);
    instr.Rn = getRegisterNumber(tokens[2]);
    instr.Rm = getRegisterNumber(tokens[3]);
    instr.shamt = 0; // Example; adjust as needed.

    uint32_t instruction = (instr.opcode << 21) | (instr.Rm << 16) | (instr.shamt << 10) | (instr.Rn << 5) | instr.Rd;
    //std::cout<<std::hex<<std::setw(8)<<std::setfill('0')<<instruction<<"\n";
    return instruction; // Cast to uint32_t for output.
}

uint32_t encodeDIstruction(std::vector<std::string>& tokens) {
    DInstruction instr;
    for (auto& i : tokens) {
        i.erase(std::remove_if(i.begin(), i.end(), [](char c) {
            return c == '[' || c == ']' || c == '#';
        }), i.end());
    }
    instr.opcode = calculateOpcode(tokens[0]);
    instr.Rt = getRegisterNumber(tokens[1]);
    instr.Rn = getRegisterNumber(tokens[2]);
    instr.op2 = 0;
    // number can be in dec #, hex #0x, or binary #0b
    std::string number = tokens[3];

    if(number[0] == '0' && number[1] == 'x') {
        number.erase(0, 2);
        instr.addr = std::stoi(number, nullptr, 16);
    } else if(number[0] == '0' && number[1] == 'b') {
        number.erase(0, 2);
        instr.addr = std::stoi(number, nullptr, 2);
    } else {
        instr.addr = std::stoi(number);
    }


    uint32_t instruction = (instr.opcode << 21) | (instr.addr << 12) | (instr.op2 << 10) | (instr.Rn << 5) | instr.Rt;
    //std::cout<<std::hex<<std::setw(8)<<std::setfill('0')<<instruction<<"\n";
    return instruction;
}


uint32_t encodeCBInstruction(std::vector<std::string>& tokens) {
    CBInstruction instr;
    for (auto& i : tokens) {
        i.erase(std::remove_if(i.begin(), i.end(), [](char c) {
            return c == '#';
        }), i.end());
    }
    instr.opcode = calculateOpcode(tokens[0]);
    instr.Rt = getRegisterNumber(tokens[1]);

    std::string number = tokens[2];
    if(number[0] == '0' && number[1] == 'x') {
        number.erase(0, 2);
        instr.imm = std::stoi(number, nullptr, 16);
    } else if(number[0] == '0' && number[1] == 'b') {
        number.erase(0, 2);
        instr.imm = std::stoi(number, nullptr, 2);
    } else {
        instr.imm = std::stoi(number);
    }

    uint32_t instruction = ((instr.opcode) << 24) |
                           ((instr.imm & 0x7FFFF) << 5) |
                           (instr.Rt & 0x1F);

    //std::cout<<std::hex<<std::setw(8)<<std::setfill('0')<<instruction<<"\n";
    return instruction;
}


std::vector<uint32_t> compile(const std::vector<std::string>& assemblyLines, const std::string& outputFileName) {

    std::vector<uint32_t> machineCode;
    for (const auto& line : assemblyLines) {
        auto tokens = tokenize(line);
        // Determine instruction format and call the appropriate encoder.
        if (instructionSet.at(tokens[0]).format == InstructionFormat::R) {
            machineCode.push_back(encodeRInstruction(tokens));
        }
        else if (instructionSet.at(tokens[0]).format == InstructionFormat::D) {
            machineCode.push_back(encodeDIstruction(tokens));
        }
        else if(instructionSet.at(tokens[0]).format == InstructionFormat::CB) {
            machineCode.push_back(encodeCBInstruction(tokens));
        }
        else {
            std::cerr << "Error: Unsupported instruction format!" << "\n";
            return machineCode;
        }

    }
    // Write machine code to file or output
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: Could not open output file for writing!" << "\n";
        return machineCode;
    }

    for (const auto& code : machineCode) {
        outputFile.write(reinterpret_cast<const char*>(&code), sizeof(uint32_t));
    }

    outputFile.close();

    if (!outputFile) {
        std::cerr << "Error: Failed to write machine code to file!" << "\n";
    } else {
        //std::cout << "Machine code successfully written to output.bin" << "\n";
    }
    return machineCode;
}
