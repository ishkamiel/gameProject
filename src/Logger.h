#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <cstdarg>

namespace pdGame 
{
    class Logger 
    {
        private:
            const std::string PREFIX_ERROR  = "[!!]> ";
            const std::string PREFIX_WARN   = "[--]> ";
            const std::string PREFIX_INFO   = "[__]> ";
            const std::string PREFIX_DEBUG  = "[..]> ";

        public:
            enum LogLevel
            {
                error,
                warn,
                info,
                debug
            };

            static Logger getLogger();

            inline void log(LogLevel l, std::string s) 
            {
                switch(l) 
                {
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
}

#endif
