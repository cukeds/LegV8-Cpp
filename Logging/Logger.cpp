#include "Logger.h"

namespace Logging {

    std::unique_ptr<Logger> Logger::instance = nullptr;
    std::mutex Logger::mutex_;

    template<>
    std::string Logger::toString<uint32_t>(const uint32_t& value) const {
        std::stringstream ss;
        ss << "0x" << std::hex << std::setw(8) << std::setfill('0') << value;
        return ss.str();
    }

    template<>
    std::string Logger::toString<uint64_t>(const uint64_t& value) const {
        std::stringstream ss;
        ss << "0x" << std::hex << std::setw(16) << std::setfill('0') << value;
        return ss.str();
    }

    template<>
    std::string Logger::toString<uint16_t>(const uint16_t& value) const {
        std::stringstream ss;
        ss << "0x" << std::hex << std::setw(4) << std::setfill('0') << value;
        return ss.str();
    }

    template<>
    std::string Logger::toString<uint8_t>(const uint8_t& value) const {
        std::stringstream ss;
        ss << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)value;
        return ss.str();
    }

    void Logger::logProcessorState(uint64_t pc, uint32_t instruction, uint16_t opcode) {
        if (currentLevel <= LogLevel::DEBUG) {
            std::stringstream ss;
            ss << "=== PROCESSOR STATE ===";
            debug(ss.str());

            logInstruction(instruction, pc);

            ss.str("");
            ss << "Opcode: 0x" << std::hex << std::setw(3) << std::setfill('0') << opcode;
            debug(ss.str());
        }
    }

    void Logger::logControlSignals(const std::string& signals) {
        if (currentLevel <= LogLevel::DEBUG) {
            debug("Control Signals: " + signals);
        }
    }

    void Logger::logCycleStart(uint64_t cycle) {
        if (currentLevel <= LogLevel::INFO) {
            std::stringstream ss;
            ss << "\n--- CYCLE " << cycle << " ---";
            info(ss.str());
        }
    }

    void Logger::logInstructionPhase(const std::string& phase) {
        if (currentLevel <= LogLevel::DEBUG) {
            std::stringstream ss;
            ss << ">> " << phase;
            debug(ss.str());
        }
    }

} // namespace Logging