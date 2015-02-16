/*
 * Strings.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: ishkamiel
 */

#include "Strings.h"

#include <ostream>
#include <string>

namespace pdUtils 
{
    std::string getTrimmed(std::string s, Trim trimOption)
    {
        return trim(s, trimOption);
    }


    std::string& trim(std::string& s, Trim trimOption)
    {
        switch(trimOption) 
        {
            case (Trim::defaultTrim):
            case (Trim::endOnNewLine):
                {
                    break;
                }
        }

        if (trimOption == Trim::endOnNewLine)
            s.append("\n");

        return (s);
    }
}
