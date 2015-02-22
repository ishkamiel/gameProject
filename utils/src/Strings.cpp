/*
 * Strings.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: ishkamiel
 */

#include "Strings.h"

#include <ostream>
#include <string>
#include <regex>

namespace pdUtils 
{
    std::string getTrimmed(std::string s, TrimOption trimOption)
    {
        return trim(s, trimOption);
    }


    std::string& trim(std::string& s, TrimOption trimOption)
    {
        switch(trimOption) 
        {
            case (TrimOption::defaultTrim):
            case (TrimOption::endOnNewline):
                {
                    std::regex space { "\\s*$" };
                    s = std::regex_replace(s, space, "");
                    break;
                }
        }

        if (trimOption == TrimOption::endOnNewline)
            s.append("\n");

        return (s);
    }
}
