/*
 * Logger.h
 *
 *  Created on: Feb 10, 2015
 *      Author: ishkamiel
 */
#ifndef PDUTILS_LOGGER_H_
#define PDUTILS_LOGGER_H_

#include "pdStrings.h"

#include <iostream>
#include <cstdarg>
#include <memory>

namespace pdUtils
{
	class Logger;
	class Writer;
	class Formatter;

	enum class LogLevel
	{
		error, warn, info, debug
	};

	typedef std::shared_ptr<Writer> WriterPtr;
	typedef std::shared_ptr<Formatter> FormatterPtr;
	typedef std::shared_ptr<Logger> LoggerSharedPtr;

	LoggerSharedPtr getLogger();

	class Writer
	{
		public:
			virtual
			~Writer() =0;
			virtual void
			log(const std::string&) =0;
	};

	class Formatter
	{
		public:
			virtual
			~Formatter() =0;
			virtual std::string
			format(LogLevel, const std::string&) =0;
	};

	class StreamWriter : public Writer
	{
		public:
			StreamWriter(std::ostream& out = std::cerr);
			~StreamWriter();
			inline void
			log(const std::string&) override;
		private:
			std::ostream& outStream;
	};

	class BasicFormatter : public Formatter
	{
		public:
			BasicFormatter();
			~BasicFormatter();
			std::string
			format(LogLevel, const std::string&) override;
	};

	class Logger
	{
		public:
			Logger();
			Logger(WriterPtr w, FormatterPtr f);
			~Logger();

			template<typename ... Targs>
			inline void
			log(LogLevel, const std::string&, Targs ... args);

			template<typename ... Targs>
			inline void
			error(const std::string&, Targs ... args);

			template<typename ... Targs>
			inline void
			warn(const std::string&, Targs ... args);

			template<typename ... Targs>
			inline void
			info(const std::string&, Targs ... args);

			template<typename ... Targs>
			inline void
			debug(const std::string&, Targs ... args);
		private:
			FormatterPtr formatter;
			WriterPtr writer;
	};
}

#include <pdLogger_definitions.h>

#endif /* PDUTILS_LOGGER_H_ */
