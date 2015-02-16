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

    enum class TrimOption 
    {
        defaultTrim,
        endOnNewline
    };

    std::string 
    getTrimmed(std::string, TrimOption = TrimOption::defaultTrim);

    std::string& 
    trim(std::string&, TrimOption = TrimOption::defaultTrim);
}

#include "Strings_templ.h"

#endif
