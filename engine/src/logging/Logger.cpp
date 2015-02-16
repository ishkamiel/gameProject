#include "Logger.h"

#include "../utils/Strings.h"

#include <iostream>
#include <assert.h>
#include <ctime>

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
        using pdUtils::getTrimmed;
        using pdUtils::TrimOption;
        
        auto timeNow = std::time(nullptr);

        switch (l) {
            case LogLevel::error:
                return (PREFIX_ERROR +
                        std::asctime(std::localtime(&timeNow)) +
                        getTrimmed(s, TrimOption::endOnNewline));
            case LogLevel::warn:
                return (PREFIX_WARN +
                        std::asctime(std::localtime(&timeNow)) +
                        getTrimmed(s, TrimOption::endOnNewline));
            case LogLevel::info:
                return (PREFIX_INFO +
                        std::asctime(std::localtime(&timeNow)) +
                        getTrimmed(s, TrimOption::endOnNewline));
            case LogLevel::debug:
                return (PREFIX_DEBUG +
                        std::asctime(std::localtime(&timeNow)) +
                        getTrimmed(s, TrimOption::endOnNewline));
        }
        assert(false && "reached end of exhausted enum switch");
        return "";
    }
}
