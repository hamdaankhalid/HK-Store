#include "logger.hpp"
#include <string>
#include <mutex>
#include <iostream>

CustomLogger::Logger& CustomLogger::Logger::GetInstance(std::ostream& stream) {
  static Logger l(stream);
  return l;
}

std::streambuf* CustomLogger::Logger::SetOs(std::ostream& os) {
  std::unique_lock<std::mutex> lock(mu);
  return ostr.rdbuf(os.rdbuf());
}

void CustomLogger::Logger::SetDebugLevel(LogLevel dl) {
  std::unique_lock<std::mutex> lock(mu);
  debugLevel = dl;
}

void CustomLogger::Logger::LogError(std::string err) {
  std::unique_lock<std::mutex> lock(mu);
  if (debugLevel == LogLevel::None) return;
  ostr << "ERROR: " << err << std::endl;
}

void CustomLogger::Logger::LogWarning(std::string warn) {
  std::unique_lock<std::mutex> lock(mu);
  if (debugLevel == LogLevel::None || debugLevel == LogLevel::Errors) return;
  ostr << "WARNING: " << warn << std::endl;
}

void CustomLogger::Logger::LogInfo(std::string info) {
  std::unique_lock<std::mutex> lock(mu);
  if (debugLevel == LogLevel::None || debugLevel == LogLevel::Errors) return;
  ostr << "INFO: " << info << std::endl;
}
