#include<gtest/gtest.h>
#include <logger.hpp>
#include <iostream>
#include <string>

TEST(Logger, LogInfo) {

  std::ostringstream oss;
  
  CustomLogger::Logger& logger = CustomLogger::Logger::GetInstance(oss);
  logger.LogInfo("Should print");
  assert(oss && oss.str() == "INFO: Should print\n");
  oss.str("");
  oss.clear();

  logger.SetDebugLevel(CustomLogger::LogLevel::None);
  logger.LogInfo("Should NOT print now");
  assert(oss && oss.str() == "");
  oss.str("");
  oss.clear();

  logger.SetDebugLevel(CustomLogger::LogLevel::Errors);
  logger.LogInfo("Should NOT print now");
  assert(oss && oss.str() == "");
  oss.str("");
  oss.clear();
  
  logger.SetDebugLevel(CustomLogger::LogLevel::All);
  logger.LogInfo("Should print now");
  assert(oss && oss.str() == "INFO: Should print now\n");
}

TEST(Logger, LogWarning) {
  std::ostringstream oss;
  
  CustomLogger::Logger& logger = CustomLogger::Logger::GetInstance(oss);
  logger.LogWarning("Should print");
  assert(oss && oss.str() == "WARNING: Should print\n");
  oss.str("");
  oss.clear();

  logger.SetDebugLevel(CustomLogger::LogLevel::None);
  logger.LogWarning("Should NOT print now");
  assert(oss && oss.str() == "");
  oss.str("");
  oss.clear();

  logger.SetDebugLevel(CustomLogger::LogLevel::Errors);
  logger.LogWarning("Should NOT print now");
  assert(oss && oss.str() == "");
  oss.str("");
  oss.clear();
  
  logger.SetDebugLevel(CustomLogger::LogLevel::All);
  logger.LogWarning("Should print now");
  assert(oss && oss.str() == "WARNING: Should print now\n");
}

TEST(Logger, LogError) {
  std::ostringstream oss;
  
  CustomLogger::Logger& logger = CustomLogger::Logger::GetInstance(oss);
  logger.LogError("Should print");
  assert(oss && oss.str() == "ERROR: Should print\n");
  oss.str("");
  oss.clear();

  logger.SetDebugLevel(CustomLogger::LogLevel::None);
  logger.LogError("Should NOT print now");
  assert(oss && oss.str() == "");
  oss.str("");
  oss.clear();

  logger.SetDebugLevel(CustomLogger::LogLevel::Errors);
  logger.LogError("Should STILL print");
  assert(oss && oss.str() == "ERROR: Should STILL print\n");
  oss.str("");
  oss.clear();
  
  logger.SetDebugLevel(CustomLogger::LogLevel::All);
  logger.LogError("Should print now");
  assert(oss && oss.str() == "ERROR: Should print now\n");
}
