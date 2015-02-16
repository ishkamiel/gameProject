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
            
            template<typename... Targs> 
            inline void log(LogLevel, const std::string&, Targs... args);

            template<typename... Targs> 
            inline void error(const std::string&, Targs... args);

            template<typename... Targs> 
            inline void warn(const std::string&, Targs... args);

            template<typename... Targs> 
            inline void info(const std::string&, Targs... args);

            template<typename... Targs> 
            inline void debug(const std::string&, Targs... args);
        private:
            FormatterPtr formatter;
            WriterPtr writer;

    };

    /**************************
     *
     * DEFINITIONS
     *
     **************************/

    template<typename... Targs> 
    inline void Logger::log(LogLevel l, const std::string& s, Targs... args)
    {
        writer->log(formatter->format(l, getSubstitutedString(s, args...)));
    }

    template<typename... Targs> 
    inline void Logger::error(const std::string& s, Targs... args)
    {
        log(LogLevel::error, s, args...);
    }

    template<typename... Targs> 
    inline void Logger::warn(const std::string& s, Targs... args)
    {
        log(LogLevel::warn, s, args...);
    }

    template<typename... Targs> 
    inline void Logger::info(const std::string& s, Targs... args)
    {
        log(LogLevel::info, s, args...);
    }

    template<typename... Targs> 
    inline void Logger::debug(const std::string& s, Targs... args)
    {
        log(LogLevel::debug, s, args...);
    }
}

#endif
