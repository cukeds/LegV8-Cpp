#ifndef ARM_LOGGER_H
#define ARM_LOGGER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <mutex>
#include <iomanip>
#include <chrono>
#include <cstdint>
#include <vector>

namespace Logging {

    enum class LogLevel {
        TRACE = 0,    // Most detailed - every operation
        DEBUG = 1,    // Detailed debugging info
        INFO = 2,     // General information
        WARN = 3,     // Warnings
        ERROR = 4,    // Errors only
        NONE = 5      // Disables all logging
    };

    class Logger {
    private:
        static std::unique_ptr<Logger> instance;
        static std::mutex mutex_;

        LogLevel currentLevel;
        std::ofstream logFile;
        bool consoleOutput;
        bool fileOutput;
        bool timestampEnabled;
        bool colorEnabled;
        std::mutex logMutex;
        uint64_t cycleCounter;

        // Private constructor for singleton
        Logger() : currentLevel(LogLevel::INFO), consoleOutput(true), fileOutput(false),
                   timestampEnabled(true), colorEnabled(true), cycleCounter(0) {}

        std::string getCurrentTimestamp() const {
            if (!timestampEnabled) return "";

            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now.time_since_epoch()) % 1000;

            std::stringstream ss;
            ss << std::put_time(std::localtime(&time_t), "%H:%M:%S");
            ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
            return "[" + ss.str() + "] ";
        }

        std::string getLevelString(LogLevel level) const {
            if (!colorEnabled) {
                switch(level) {
                    case LogLevel::TRACE: return "[TRACE] ";
                    case LogLevel::DEBUG: return "[DEBUG] ";
                    case LogLevel::INFO:  return "[INFO]  ";
                    case LogLevel::WARN:  return "[WARN]  ";
                    case LogLevel::ERROR: return "[ERROR] ";
                    default: return "[UNKNOWN] ";
                }
            } else {
                // ANSI color codes for better visibility
                switch(level) {
                    case LogLevel::TRACE: return "\033[37m[TRACE]\033[0m ";  // White
                    case LogLevel::DEBUG: return "\033[36m[DEBUG]\033[0m ";  // Cyan
                    case LogLevel::INFO:  return "\033[32m[INFO] \033[0m ";  // Green
                    case LogLevel::WARN:  return "\033[33m[WARN] \033[0m ";  // Yellow
                    case LogLevel::ERROR: return "\033[31m[ERROR]\033[0m ";  // Red
                    default: return "[UNKNOWN] ";
                }
            }
        }

        template<typename T>
        void logImpl(LogLevel level, const T& message) {
            if (level < currentLevel) return;

            std::lock_guard<std::mutex> lock(logMutex);

            std::string timestamp = getCurrentTimestamp();
            std::string levelStr = getLevelString(level);
            std::string fullMessage = timestamp + levelStr + toString(message);

            if (consoleOutput) {
                if (level >= LogLevel::ERROR) {
                    std::cerr << fullMessage << std::endl;
                } else {
                    std::cout << fullMessage << std::endl;
                }
            }

            if (fileOutput && logFile.is_open()) {
                // Remove color codes for file output
                std::string fileMessage = timestamp + getLevelString(level) + toString(message);
                logFile << fileMessage << std::endl;
                logFile.flush();
            }
        }

        template<typename T>
        std::string toString(const T& value) const {
            std::stringstream ss;
            ss << value;
            return ss.str();
        }

    public:
        // Singleton access
        static Logger* getInstance() {
            std::lock_guard<std::mutex> lock(mutex_);
            if (instance == nullptr) {
                instance = std::unique_ptr<Logger>(new Logger());
            }
            return instance.get();
        }

        // Configuration methods
        void setLogLevel(LogLevel level) { currentLevel = level; }
        LogLevel getLogLevel() const { return currentLevel; }

        void enableConsoleOutput(bool enable) { consoleOutput = enable; }
        void enableColors(bool enable) { colorEnabled = enable; }
        void enableFileOutput(bool enable, const std::string& filename = "legv8_sim.log") {
            std::lock_guard<std::mutex> lock(logMutex);
            fileOutput = enable;
            if (enable) {
                if (logFile.is_open()) logFile.close();
                logFile.open(filename, std::ios::app);
                if (!logFile.is_open()) {
                    std::cerr << "Failed to open log file: " << filename << std::endl;
                    fileOutput = false;
                } else {
                    // Write session header
                    logFile << "\n=== NEW SIMULATION SESSION "
                            << getCurrentTimestamp() << "===" << std::endl;
                }
            } else if (logFile.is_open()) {
                logFile.close();
            }
        }

        void enableTimestamp(bool enable) { timestampEnabled = enable; }

        // Logging methods
        template<typename T>
        void trace(const T& message) { logImpl(LogLevel::TRACE, message); }

        template<typename T>
        void debug(const T& message) { logImpl(LogLevel::DEBUG, message); }

        template<typename T>
        void info(const T& message) { logImpl(LogLevel::INFO, message); }

        template<typename T>
        void warn(const T& message) { logImpl(LogLevel::WARN, message); }

        template<typename T>
        void error(const T& message) { logImpl(LogLevel::ERROR, message); }

        // Educational processor logging methods
        void logInstruction(uint32_t instruction, uint64_t pc) {
            if (currentLevel <= LogLevel::DEBUG) {
                std::stringstream ss;
                ss << "PC: 0x" << std::hex << std::setw(16) << std::setfill('0') << pc
                   << " | Instruction: 0x" << std::setw(8) << instruction;
                debug(ss.str());
            }
        }

        void logRegister(uint8_t regNum, uint64_t value) {
            if (currentLevel <= LogLevel::TRACE) {
                std::stringstream ss;
                ss << "X" << std::dec << (int)regNum << " = 0x"
                   << std::hex << std::setw(16) << std::setfill('0') << value;
                trace(ss.str());
            }
        }

        void logRegisterSet(uint8_t regNum, uint64_t oldValue, uint64_t newValue) {
            if (currentLevel <= LogLevel::DEBUG) {
                std::stringstream ss;
                ss << "X" << std::dec << (int)regNum << ": 0x"
                   << std::hex << std::setw(16) << std::setfill('0') << oldValue
                   << " -> 0x" << std::setw(16) << newValue;
                debug(ss.str());
            }
        }

        void logMemoryAccess(uint64_t address, uint64_t value, bool isWrite, int size = 64) {
            if (currentLevel <= LogLevel::DEBUG) {
                std::stringstream ss;
                ss << (isWrite ? "STORE" : "LOAD") << size << " @ 0x"
                   << std::hex << std::setw(16) << std::setfill('0') << address
                   << " = 0x" << std::setw(size/4) << value;
                debug(ss.str());
            }
        }

        void logALUOperation(const std::string& operation, uint64_t a, uint64_t b, uint64_t result) {
            if (currentLevel <= LogLevel::DEBUG) {
                std::stringstream ss;
                ss << "ALU: " << operation << "(0x" << std::hex << std::setw(16) << std::setfill('0') << a
                   << ", 0x" << std::setw(16) << b << ") = 0x" << std::setw(16) << result;
                debug(ss.str());
            }
        }

        void logBranch(bool taken, uint64_t currentPC, uint64_t targetPC) {
            if (currentLevel <= LogLevel::DEBUG) {
                std::stringstream ss;
                ss << "BRANCH from 0x" << std::hex << std::setw(16) << std::setfill('0') << currentPC;
                if (taken) {
                    ss << " TAKEN -> 0x" << std::setw(16) << targetPC;
                } else {
                    ss << " NOT TAKEN";
                }
                debug(ss.str());
            }
        }

        void logControlSignals(const std::string& signals) {
            if (currentLevel <= LogLevel::TRACE) {
                trace("Control: " + signals);
            }
        }

        void logProcessorState(uint64_t pc, uint32_t instruction, uint16_t opcode) {
            if (currentLevel <= LogLevel::DEBUG) {
                std::stringstream ss;
                ss << "--- FETCH: PC=0x" << std::hex << std::setw(16) << std::setfill('0') << pc
                   << " INSTR=0x" << std::setw(8) << instruction
                   << " OPCODE=0x" << std::setw(3) << opcode << " ---";
                debug(ss.str());
            }
        }

        void logCycleStart(uint64_t cycle) {
            cycleCounter = cycle;
            if (currentLevel <= LogLevel::INFO) {
                std::stringstream ss;
                ss << "\n========== CYCLE " << std::dec << cycle << " ==========";
                info(ss.str());
            }
        }

        void logInstructionPhase(const std::string& phase) {
            if (currentLevel <= LogLevel::DEBUG) {
                debug("Phase: " + phase);
            }
        }

        void logInstructionDecode(const std::string& mnemonic, uint8_t rd, uint8_t rn, uint8_t rm) {
            if (currentLevel <= LogLevel::DEBUG) {
                std::stringstream ss;
                ss << "DECODE: " << mnemonic << " X" << (int)rd << ", X" << (int)rn << ", X" << (int)rm;
                debug(ss.str());
            }
        }

        void logInstructionDecodeImm(const std::string& mnemonic, uint8_t rd, uint8_t rn, uint64_t imm) {
            if (currentLevel <= LogLevel::DEBUG) {
                std::stringstream ss;
                ss << "DECODE: " << mnemonic << " X" << (int)rd << ", X" << (int)rn
                   << ", #0x" << std::hex << imm;
                debug(ss.str());
            }
        }

        // Educational summary methods
        void logExecutionSummary(uint64_t totalCycles, uint64_t totalInstructions) {
            if (currentLevel <= LogLevel::INFO) {
                std::stringstream ss;
                ss << "\n=== EXECUTION SUMMARY ===";
                info(ss.str());
                ss.str("");
                ss << "Total Cycles: " << std::dec << totalCycles;
                info(ss.str());
                ss.str("");
                ss << "Total Instructions: " << totalInstructions;
                info(ss.str());
                if (totalCycles > 0) {
                    ss.str("");
                    ss << "CPI (Cycles Per Instruction): " << std::fixed << std::setprecision(2)
                       << (double)totalCycles / totalInstructions;
                    info(ss.str());
                }
            }
        }

        // Template specializations for hex formatting
        template<> std::string toString<uint32_t>(const uint32_t& value) const;
        template<> std::string toString<uint64_t>(const uint64_t& value) const;
        template<> std::string toString<uint16_t>(const uint16_t& value) const;
        template<> std::string toString<uint8_t>(const uint8_t& value) const;

        // Destructor
        ~Logger() {
            if (logFile.is_open()) {
                logFile << "=== SIMULATION SESSION END ===" << std::endl;
                logFile.close();
            }
        }

        // Delete copy constructor and assignment operator
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
    };

} // namespace Logging

// Convenience macros for easier usage
#define LOG_TRACE(msg) Logging::Logger::getInstance()->trace(msg)
#define LOG_DEBUG(msg) Logging::Logger::getInstance()->debug(msg)
#define LOG_INFO(msg) Logging::Logger::getInstance()->info(msg)
#define LOG_WARN(msg) Logging::Logger::getInstance()->warn(msg)
#define LOG_ERROR(msg) Logging::Logger::getInstance()->error(msg)

// Specialized macros for processor operations
#define LOG_INSTRUCTION(instr, pc) Logging::Logger::getInstance()->logInstruction(instr, pc)
#define LOG_REGISTER(reg, val) Logging::Logger::getInstance()->logRegister(reg, val)
#define LOG_REGISTER_SET(reg, old, new_val) Logging::Logger::getInstance()->logRegisterSet(reg, old, new_val)
#define LOG_MEMORY(addr, val, write, size) Logging::Logger::getInstance()->logMemoryAccess(addr, val, write, size)
#define LOG_ALU(op, a, b, result) Logging::Logger::getInstance()->logALUOperation(op, a, b, result)
#define LOG_BRANCH(taken, current, target) Logging::Logger::getInstance()->logBranch(taken, current, target)
#define LOG_CONTROL(signals) Logging::Logger::getInstance()->logControlSignals(signals)
#define LOG_PROCESSOR_STATE(pc, instr, opcode) Logging::Logger::getInstance()->logProcessorState(pc, instr, opcode)
#define LOG_CYCLE(cycle) Logging::Logger::getInstance()->logCycleStart(cycle)
#define LOG_PHASE(phase) Logging::Logger::getInstance()->logInstructionPhase(phase)
#define LOG_DECODE(mnemonic, rd, rn, rm) Logging::Logger::getInstance()->logInstructionDecode(mnemonic, rd, rn, rm)
#define LOG_DECODE_IMM(mnemonic, rd, rn, imm) Logging::Logger::getInstance()->logInstructionDecodeImm(mnemonic, rd, rn, imm)

#endif //ARM_LOGGER_H