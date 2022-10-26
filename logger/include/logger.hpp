#pragma once
#include<string>

namespace CustomLogger {
  enum LogLevel { Errors, All, None };

  class Logger {
    public:
    static Logger& GetInstance();

    void SetDebugLevel(LogLevel dl);

    void LogError(std::string err);
    
    void LogWarning(std::string warn);
    
    void LogInfo(std::string inf);
    
    private:

    LogLevel debugLevel = All;
  };
};

