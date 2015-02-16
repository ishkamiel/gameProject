/*
 * Strings.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: ishkamiel
 */

#include "Strings.h"

namespace pdUtils 
{
    std::string getTrimmed(std::string s)
    {
        return (s);
    }

    std::string& trim(std::string& s)
    {
        return (s);
    }
}

/*
 * Just for reference on template instantiation
template bool operator==<char>(const pdString<char>& s, const pdString<char>& other);
template bool operator==<char>(const pdString<char>& s, const char* other);
template bool operator!=<char>(const pdString<char>& s, const pdString<char>& other);
template bool operator!=<char>(const pdString<char>& s, const char* other);
template std::ostream &operator<<<char> (std::ostream&, const pdString<char>&
template class pdString<char>;
*/
