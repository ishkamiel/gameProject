#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H

#include <string>

namespace pdUtils
{
    inline void formatString(std::string&) {}

    template<typename T, typename... Targs>
    inline void formatString(std::string& s, T value, Targs... args) 
    {
        auto pos = s.find("%") + 1;

        while(pos < s.length()) {
            switch (s.at(pos)) 
            {
                case('%'):
                    pos = s.find("%", pos) + 1;
                case('d'):
                    s.replace(pos-1, 2, value);
                    parsef(s, args...);
                default:
                    return;
            }
        }
    }

    inline std::string getFormatedString(const std::string& s) 
    {
        std::string retval {s};
        return s;
    }

    template<typename T, typename... Targs> 
    inline std::string getFormatedString(const std::string& s, T a, Targs... args)
    {
        std::string retval {s};
        substituteArgs(retval, a, args...);
        return retval;
    }
}


#endif
