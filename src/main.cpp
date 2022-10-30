#include <logger.hpp>

int main(int argc, char* argv[]) {
  CustomLogger::Logger& logger = CustomLogger::Logger::GetInstance(std::cout);
  
}
