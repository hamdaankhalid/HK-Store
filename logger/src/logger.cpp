#include "logger.hpp"
#include <string>
#include <iostream>

CustomLogger::Logger& CustomLogger::Logger::GetInstance(std::ostream& stream) {
  static Logger l(stream);
  return l;
}

std::streambuf* CustomLogger::Logger::SetOs(std::ostream& os) {
  return ostr.rdbuf(os.rdbuf());
}

void CustomLogger::Logger::SetDebugLevel(LogLevel dl) {
  debugLevel = dl;
}

void CustomLogger::Logger::LogError(std::string err) {
  if (debugLevel == LogLevel::None) return;
  ostr << "ERROR: " << err << std::endl;
}

void CustomLogger::Logger::LogWarning(std::string warn) {
  if (debugLevel == LogLevel::None || debugLevel == LogLevel::Errors) return;
  ostr << "WARNING: " << warn << std::endl;
}

void CustomLogger::Logger::LogInfo(std::string info) {
  if (debugLevel == LogLevel::None || debugLevel == LogLevel::Errors) return;
  ostr << "INFO: " << info << std::endl;
}
