/*
 * Logger_templates.h
 *
 *  Created on: Feb 16, 2015
 *      Author: ishkamiel
 */

#ifndef PDUTILS_LOGGER_DEFINITIONS_H_
#define PDUTILS_LOGGER_DEFINITIONS_H_

#include "pdLogger.h"

namespace pdUtils
{
    template<typename... Targs>
    inline void Logger::log(LogLevel l, const std::string& s, Targs... args)
    {
    	writer->log(formatter->format(l, pdUtils::getFormatedString(s, args...)));
    }

    template<typename... Targs>
    inline void Logger::error(const std::string& s, Targs... args)
    {
    	log(LogLevel::error, s, args...);
    }

    template<typename... Targs>
    inline void Logger::warn(const std::string& s, Targs... args)
    {
    	log(LogLevel::warn, s, args...);
    }

    template<typename... Targs>
    inline void Logger::info(const std::string& s, Targs... args)
    {
    	log(LogLevel::info, s, args...);
    }

    template<typename... Targs>
    inline void Logger::debug(const std::string& s, Targs... args)
    {
    	log(LogLevel::debug, s, args...);
    }
}

#endif /* PDUTILS_LOGGER_DEFINITIONS_H_ */
