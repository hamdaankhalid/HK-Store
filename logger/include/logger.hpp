#pragma once

#include <string>
#include <iostream>

namespace CustomLogger {
  enum LogLevel { Errors, All, None };

  class Logger {
    public:
    static Logger& GetInstance(std::ostream& stream);

    void SetDebugLevel(LogLevel dl);

    std::streambuf* SetOs(std::ostream& os);

    void LogError(std::string err);
    
    void LogWarning(std::string warn);
    
    void LogInfo(std::string inf);


    template <typename T> friend Logger& operator<<(Logger& os, const T& t)
    { os.ostr << t; return os; }

    friend Logger& operator<<(Logger& os, std::ostream& ( *pf )(std::ostream&))
    { os.ostr << pf; return os; }

    
    private:
    Logger(std::ostream& ost) : ostr(ost.rdbuf()){};

    LogLevel debugLevel = LogLevel::All;
    std::ostream ostr;
  };
};

