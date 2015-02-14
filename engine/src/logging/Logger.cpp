#include "Logger.h"

#include <iostream>
#include <assert.h>

namespace pdLogger {
    /*
     * Declarations
     */

    class StreamWriter : public Logger::Writer {
        public: 
            StreamWriter(std::ostream& out = std::cerr);
            ~StreamWriter();
            inline void log(const std::string&) override;
        private:
            std::ostream& outStream;
    };

    class BasicFormatter : public Logger::Formatter {
        public:
            BasicFormatter();
            ~BasicFormatter();
            std::string format(LogLevel, const std::string&) override;
    };

    /*
     * Definitions
     */

    Logger::Logger(WriterPtr w, FormatterPtr f)
        : formatter(f), writer(w) {}

    Logger::Logger()
        : formatter(new BasicFormatter()), writer(new StreamWriter()) {}

    Logger::~Logger() {}


    const std::string PREFIX_ERROR = "[!!]> ";
    const std::string PREFIX_WARN = "[--]> ";
    const std::string PREFIX_INFO = "[__]> ";
    const std::string PREFIX_DEBUG = "[..]> ";

    LoggerPtr getLogger()
    {
        static LoggerPtr logger { new Logger() };
        return logger;
    }

    Logger::Writer::~Writer() {}

    Logger::Formatter::~Formatter() {}

    /*
     * ConsoleLogger
     */

    StreamWriter::StreamWriter(std::ostream& out)
        : outStream(out) {}

    StreamWriter::~StreamWriter() {}

    inline void StreamWriter::log(const std::string& s)
    {
        outStream << s;
    }

    /*
     * BasicFormatter
     */

    BasicFormatter::BasicFormatter() {};

    BasicFormatter::~BasicFormatter() {};

    inline std::string BasicFormatter::format(LogLevel l, const std::string& s)
    {
        switch (l) {
            case LogLevel::error:
                return PREFIX_ERROR + s;
            case LogLevel::warn:
                return PREFIX_WARN + s;
            case LogLevel::info:
                return PREFIX_INFO + s;
            case LogLevel::debug:
                return PREFIX_DEBUG + s;
            default:
                assert(false && "reached end of exhausted enum switch");
                return "";
        }
    }
}
