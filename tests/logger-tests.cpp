#include<gtest/gtest.h>
#include <logger.hpp>
#include <iostream>
#include <string>

TEST(Logger, exploration) {
  CustomLogger::Logger& logger = CustomLogger::Logger::GetInstance();
  logger.LogInfo("Should print");
  logger.SetDebugLevel(CustomLogger::LogLevel::None);
  logger.LogInfo("Should not print now");
  logger.SetDebugLevel(CustomLogger::LogLevel::All);
  logger.LogInfo("Should print now");
}
