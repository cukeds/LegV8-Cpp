//
// Logger.cpp - Implementation of the logging system
//

#include "Logger.h"

namespace Logging {

// Static member definitions
std::unique_ptr<Logger> Logger::instance = nullptr;
std::mutex Logger::mutex_;

} // namespace Logging