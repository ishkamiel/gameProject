#include "Logger.h"
#include "Strings.h"

#include <iostream>
#include <assert.h>
#include <ctime>

namespace pdLogger {
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
        return(logger);
    }

    Writer::~Writer() {}

    Formatter::~Formatter() {}

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
                return (
                        getTrimmed(std::asctime(std::localtime(&timeNow))) +
                        PREFIX_ERROR +
                        getTrimmed(s, TrimOption::endOnNewline)
                        );
            case LogLevel::warn:
                return (
                        getTrimmed(std::asctime(std::localtime(&timeNow))) +
                        PREFIX_WARN +
                        getTrimmed(s, TrimOption::endOnNewline)
                        );
            case LogLevel::info:
                return (
                        getTrimmed(std::asctime(std::localtime(&timeNow))) +
                        PREFIX_INFO +
                        getTrimmed(s, TrimOption::endOnNewline)
                        );
            case LogLevel::debug:
                return (
                        getTrimmed(std::asctime(std::localtime(&timeNow))) +
                        PREFIX_DEBUG +
                        getTrimmed(s, TrimOption::endOnNewline)
                        );
        }
        assert(false && "reached end of exhausted enumerated switch");
        return("");
    }
}
