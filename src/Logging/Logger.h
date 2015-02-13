#ifndef LOGGER_H
#define LOGGER_H

#include <iostream> 
#include <cstdarg> 
#include <memory>

namespace pdLogger {
    static const std::string PREFIX_ERROR = "[!!]> ";
    static const std::string PREFIX_WARN = "[--]> ";
    static const std::string PREFIX_INFO = "[__]> ";
    static const std::string PREFIX_DEBUG = "[..]> ";

    enum class LogLevel {
        error,
        warn,
        info,
        debug
    };

    void log(LogLevel, std::string);
    
    class Writer {
        public:
            virtual ~Writer() =0;
            virtual void log(std::string) =0;
    };

    class Formatter {
        public:
            virtual ~Formatter() =0;
            virtual std::string format(LogLevel, std::string) =0;
    };

    class Logger {
        public: 
            Logger(Writer& w, Formatter& f);
            ~Logger();
            inline void log(LogLevel, std::string);
        private:
            Formatter& formatter;
            Writer& writer;
    };

    Logger::Logger(Writer& w, Formatter& f)
        : formatter(f), writer(w) {}

    Logger::~Logger() {}

    inline void Logger::log(LogLevel l, std::string s)
    {
        writer.log(formatter.format(l, s));
    }
}

#endif
