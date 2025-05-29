//
// Logger.h - Comprehensive logging system for LegV8 simulator
//

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

namespace Logging {

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3,
    NONE = 4  // Disables all logging
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
    std::mutex logMutex;
    
    // Private constructor for singleton
    Logger() : currentLevel(LogLevel::INFO), consoleOutput(true), fileOutput(false), timestampEnabled(true) {}
    
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
        switch(level) {
            case LogLevel::DEBUG: return "[DEBUG] ";
            case LogLevel::INFO:  return "[INFO]  ";
            case LogLevel::WARN:  return "[WARN]  ";
            case LogLevel::ERROR: return "[ERROR] ";
            default: return "[UNKNOWN] ";
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
            logFile << fullMessage << std::endl;
            logFile.flush();
        }
    }
    
    template<typename T>
    std::string toString(const T& value) const {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
    
    // Specialization for hex formatting
    std::string toString(const std::pair<const char*, uint64_t>& hexPair) const {
        std::stringstream ss;
        ss << hexPair.first << "0x" << std::hex << std::setw(16) << std::setfill('0') << hexPair.second;
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
    void enableFileOutput(bool enable, const std::string& filename = "legv8_sim.log") {
        std::lock_guard<std::mutex> lock(logMutex);
        fileOutput = enable;
        if (enable) {
            if (logFile.is_open()) logFile.close();
            logFile.open(filename, std::ios::app);
            if (!logFile.is_open()) {
                std::cerr << "Failed to open log file: " << filename << std::endl;
                fileOutput = false;
            }
        } else if (logFile.is_open()) {
            logFile.close();
        }
    }
    
    void enableTimestamp(bool enable) { timestampEnabled = enable; }
    
    // Logging methods
    template<typename T>
    void debug(const T& message) { logImpl(LogLevel::DEBUG, message); }
    
    template<typename T>
    void info(const T& message) { logImpl(LogLevel::INFO, message); }
    
    template<typename T>
    void warn(const T& message) { logImpl(LogLevel::WARN, message); }
    
    template<typename T>
    void error(const T& message) { logImpl(LogLevel::ERROR, message); }
    
    // Convenience methods for common processor logging patterns
    void logInstruction(uint32_t instruction, uint64_t pc) {
        if (currentLevel <= LogLevel::DEBUG) {
            std::stringstream ss;
            ss << "PC: 0x" << std::hex << std::setw(16) << std::setfill('0') << pc 
               << " Instruction: 0x" << std::setw(8) << instruction;
            debug(ss.str());
        }
    }
    
    void logRegister(uint8_t regNum, uint64_t value) {
        if (currentLevel <= LogLevel::DEBUG) {
            std::stringstream ss;
            ss << "Register X" << (int)regNum << ": 0x" 
               << std::hex << std::setw(16) << std::setfill('0') << value;
            debug(ss.str());
        }
    }
    
    void logMemoryAccess(uint64_t address, uint64_t value, bool isWrite, int size = 64) {
        if (currentLevel <= LogLevel::DEBUG) {
            std::stringstream ss;
            ss << (isWrite ? "Write" : "Read") << size << " - Address: 0x" 
               << std::hex << std::setw(16) << std::setfill('0') << address
               << " Value: 0x" << std::setw(size/4) << value;
            debug(ss.str());
        }
    }
    
    void logALUOperation(const std::string& operation, uint64_t a, uint64_t b, uint64_t result) {
        if (currentLevel <= LogLevel::DEBUG) {
            std::stringstream ss;
            ss << "ALU " << operation << ": 0x" << std::hex << std::setw(16) << std::setfill('0') << a
               << " " << operation << " 0x" << std::setw(16) << b << " = 0x" << std::setw(16) << result;
            debug(ss.str());
        }
    }
    
    void logBranch(bool taken, uint64_t targetPC) {
        if (currentLevel <= LogLevel::DEBUG) {
            std::stringstream ss;
            ss << "Branch " << (taken ? "taken" : "not taken");
            if (taken) {
                ss << " to 0x" << std::hex << std::setw(16) << std::setfill('0') << targetPC;
            }
            debug(ss.str());
        }
    }
    
    // Destructor
    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    
    // Delete copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

} // namespace Logging

// Convenience macros for easier usage
#define LOG_DEBUG(msg) Logging::Logger::getInstance()->debug(msg)
#define LOG_INFO(msg) Logging::Logger::getInstance()->info(msg)
#define LOG_WARN(msg) Logging::Logger::getInstance()->warn(msg)
#define LOG_ERROR(msg) Logging::Logger::getInstance()->error(msg)

// Specialized macros for processor operations
#define LOG_INSTRUCTION(instr, pc) Logging::Logger::getInstance()->logInstruction(instr, pc)
#define LOG_REGISTER(reg, val) Logging::Logger::getInstance()->logRegister(reg, val)
#define LOG_MEMORY(addr, val, write, size) Logging::Logger::getInstance()->logMemoryAccess(addr, val, write, size)
#define LOG_ALU(op, a, b, result) Logging::Logger::getInstance()->logALUOperation(op, a, b, result)
#define LOG_BRANCH(taken, target) Logging::Logger::getInstance()->logBranch(taken, target)

#endif //ARM_LOGGER_H