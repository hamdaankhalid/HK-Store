#include "logger.hpp"
#include <string>
#include <iostream>

CustomLogger::Logger& CustomLogger::Logger::GetInstance() {
  static Logger l;
  return l;
}

void CustomLogger::Logger::SetDebugLevel(LogLevel dl) {
  debugLevel = dl;
}

void CustomLogger::Logger::LogError(std::string err) {
  if (debugLevel == LogLevel::None) return;
  std::cout << "ERROR: " << err << std::endl;
}

void CustomLogger::Logger::LogWarning(std::string warn) {
  if (debugLevel == LogLevel::None || debugLevel == LogLevel::Errors) return;
  std::cout << "WARNING: " << warn << std::endl;
}

void CustomLogger::Logger::LogInfo(std::string info) {
  if (debugLevel == LogLevel::None || debugLevel == LogLevel::Errors) return;
  std::cout << "INFO: " << info << std::endl;
}
