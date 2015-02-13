#include "Logger.h"

#include <iostream>
#include <assert.h>

namespace pdLogger {
    Logger::Logger(Writer& w, Formatter& f)
        : formatter(f), writer(w) {}

    Logger::~Logger() {}

    void Logger::log(LogLevel l, std::string s)
    {
        writer.log(formatter.format(l, s));
    }

    class StreamWriter : public Writer {
        public: 
            StreamWriter(std::ostream& out = std::cerr);
            ~StreamWriter();
            inline void log(std::string) override;
        private:
            std::ostream& outStream;
    };

    class BasicFormatter : public Formatter {
        public:
            BasicFormatter();
            ~BasicFormatter();
            std::string format(LogLevel, std::string) override;
    };
}

namespace pdLogger {
    void log(LogLevel l, std::string s)
    {
        static StreamWriter w {};
        static BasicFormatter f {};
        static Logger logger { w, f };
        logger.log(l, s);
    }

    Writer::~Writer() {}

    Formatter::~Formatter() {}

    /*
     * ConsoleLogger
     */

    StreamWriter::StreamWriter(std::ostream& out)
        : outStream(out) {}

    StreamWriter::~StreamWriter() {}

    inline void StreamWriter::log(std::string s)
    {
        outStream << s;
    }

    /*
     * BasicFormatter
     */

    BasicFormatter::BasicFormatter() {};

    BasicFormatter::~BasicFormatter() {};

    inline std::string BasicFormatter::format(LogLevel l, std::string s)
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
