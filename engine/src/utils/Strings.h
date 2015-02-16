/*
 * Strings.h
 *
 *  Created on: Feb 15, 2015
 *      Author: ishkamiel
 */

#ifndef STRINGS_H_
#define STRINGS_H_

#include <string>
#include <sstream>
#include <iostream>

namespace pdUtils
{
	typedef unsigned int string_pos;

	/**
	 *
	 * @param
	 * @return
	 */
	template<typename T>
		inline std::string
		stringify(const T&);

	/**
	 *
	 * @param
	 * @return
	 */
	inline std::string&
	formatString(std::string&);

	/**
	 *
	 * @param
	 * @param
	 * @param
	 * @return
	 */
	template<typename T, typename ... Targs>
		inline std::string&
		formatString(std::string&, T, Targs...);

	/**
	 *
	 * @param
	 * @return
	 */
	inline std::string
	getFormatedString(const std::string&);

	/**
	 *
	 * @param
	 * @param
	 * @param
	 * @return
	 */
	template<typename T, typename ... Targs>
		inline std::string
		getFormatedString(const std::string&, T, Targs ...);

	static inline std::string&
	p_formatString(string_pos, std::string&);

	template<typename T, typename ... Targs>
		static inline std::string&
		p_formatString(string_pos, std::string&, T, Targs...);
}

/*
 * Definitions for template functions
 */

template<typename T>
inline std::string
pdUtils::stringify(const T& value)
{
    std::stringstream ss;
    std::string retval;
    ss << value;
    ss >> retval;
    return (retval);
}

inline std::string&
pdUtils::formatString(std::string& s)
{
	return (p_formatString(0, s));
}

template<typename T, typename ... Targs>
inline std::string&
pdUtils::formatString(std::string& s, T value, Targs ... args)
{
    return (p_formatString(0, s, value, args...));
}

inline std::string
pdUtils::getFormatedString(const std::string& s)
{
	std::string retval { s };
	formatString(retval);
	return (retval);
}

template<typename T, typename ... Targs>
inline std::string
pdUtils::getFormatedString(const std::string& s, T a, Targs ... args)
{
    std::string retval { s };
    formatString(retval, a, args...);
    return (retval);
}

inline std::string&
pdUtils::p_formatString(string_pos start, std::string& s)
{
	auto pos = s.find("%%", start);

	if (pos != std::string::npos)
	{
		s.replace(pos, 1, "");
		p_formatString(pos + 1, s);
	}

	return (s);
}

template<typename T, typename ... Targs>
inline std::string&
pdUtils::p_formatString(string_pos start, std::string& s, T v, Targs ... args)
{
    auto pos = s.find("%", start);

    if (pos != std::string::npos && pos < s.length() - 1)
    {
        ++pos;
        switch (s.at(pos))
        {
            case ('%'):
                {
                    s.replace(pos, 1, "");
                    p_formatString(pos, s, v, args...);
                    break;
                }
            case ('d'):
            case ('i'):
            case ('f'):
                {
                    std::string r = stringify(v);
                    s.replace(pos - 1, 2, r, 0, std::string::npos);
                    p_formatString(pos + r.length() - 1, s, args...);
                    break;
                }
            default: 
                {
                    std::cerr << "   is unknown" << std::endl;
                    p_formatString(pos, s, args...);
                }
        }
    }
    return (s);
}

#endif
