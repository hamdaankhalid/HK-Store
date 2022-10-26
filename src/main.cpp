#include <logger.hpp>

int main(int argc, char* argv[]) {
  CustomLogger::Logger logger = CustomLogger::Logger::GetInstance();

  if (argc != 3) {
    logger.LogInfo("Add args for file path to Nginx Info Log file and Nginx Error log file");
    return -1;
  }
}
