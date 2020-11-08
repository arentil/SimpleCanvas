#pragma once

#include "Core.h"

#include <mutex>
#include <string>

namespace sc
{
	class SC_API Logger
	{
		mutable std::mutex mutex;

		Logger() = default;
	public:
		static Logger& instance()
		{
			static Logger l;
			return l;
		}

		Logger(Logger const&) = delete;
		void operator=(Logger const&) = delete;
		void Log(std::string const& text);
		void LogInfo(std::string const& text);
		void LogError(std::string const& text);
	};

#define LOG_TEXT(text) simpleCanvas::Logger::instance().Log(text)
}