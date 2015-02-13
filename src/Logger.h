#ifndef LOGGER_H
#define LOGGER_H

#include <iostream> 
#include <cstdarg> 
#include <memory>

namespace pdLogger {
    class Logger {
        public: Logger();
                virtual~Logger() = 0;
                virtual void log(std::string) = 0;
    };

    class ConsoleLogger: public Logger {
        public: ConsoleLogger(std::ostream out);

        private:
                std::ostream& outStream;
    };

    typedef std::shared_ptr <Logger> LoggerPtr;

    static const std::string PREFIX_ERROR = "[!!]> ";
    static const std::string PREFIX_WARN = "[--]> ";
    static const std::string PREFIX_INFO = "[__]> ";
    static const std::string PREFIX_DEBUG = "[..]> ";

    static LoggerPtr getLogger();

    inline void log(LogLevel l, std::string s) {
        switch (l) {
            case error:
                std::cerr << PREFIX_ERROR;
                break;
            case warn:
                std::cerr << PREFIX_WARN;
                break;
            case info:
                std::cerr << PREFIX_INFO;
                break;
            case debug:
                std::cerr << PREFIX_DEBUG;
                break;
        }
        std::cerr << s << "\n";
    }
};

ConsoleLogger::ConsoleLogger(std::ostream& o = std::cerr&): out(out) {}

inline void log(std::string) override {
    out << std::string;
}

#endif
