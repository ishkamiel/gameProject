#include "Logger.h"

#include <iostream>

namespace pdLogger {
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

    void log(LogLevel l, std::string s)
    {
        static StreamWriter w {};
        static BasicFormatter f {};
        static Logger logger { w, f };
        logger.log(l, s);
    }

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

    inline std::string format(LogLevel l, std::string s)
    {
        switch (l) {
            case error:
                return PREFIX_ERROR + s;
            case warn:
                return PREFIX_WARN + s;
            case info:
                return PREFIX_INFO + s;
            case debug:
                return PREFIX_DEBUG + s;
        }
    }
}
