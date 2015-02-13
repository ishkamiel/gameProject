#ifndef LOGGER_H
#define LOGGER_H

#include <iostream> 
#include <cstdarg> 
#include <memory>

namespace pdLogger {
    class Logger;

    enum class LogLevel {
        error,
        warn,
        info,
        debug
    };

    typedef std::shared_ptr<Logger> LoggerPtr;

    LoggerPtr getLogger();
    
    class Logger {
        public: 
            class Writer;
            class Formatter;

            typedef std::shared_ptr<Writer> WriterPtr;
            typedef std::shared_ptr<Formatter> FormatterPtr;

            class Writer {
                public:
                    virtual ~Writer() =0;
                    virtual void log(const std::string&) =0;
            };

            class Formatter {
                public:
                    virtual ~Formatter() =0;
                    virtual std::string format(LogLevel, const std::string&) =0;
            };

            Logger();
            Logger(WriterPtr w, FormatterPtr f);
            ~Logger();
            inline void log(LogLevel, const std::string&);
            inline void error(const std::string&);
            inline void warn(const std::string&);
            inline void info(const std::string&);
            inline void debug(const std::string&);
        private:
            FormatterPtr formatter;
            WriterPtr writer;
    };
}

namespace pdLogger {
    inline void Logger::log(LogLevel l, const std::string& s)
    {
        writer->log(formatter->format(l, s));
    }

    inline void Logger::error(const std::string& s)
    {
        log(LogLevel::error, s);
    }

    inline void Logger::warn(const std::string& s)
    {
        log(LogLevel::warn, s);
    }

    inline void Logger::info(const std::string& s)
    {
        log(LogLevel::info, s);
    }

    inline void Logger::debug(const std::string& s)
    {
        log(LogLevel::debug, s);
    }
}

#endif
