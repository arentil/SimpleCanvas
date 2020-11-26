#pragma once

#include <string>
//#include <Windows.h>
#include <mutex>
#include "Core.h"

namespace sc
{
class SC_API Logger
{
public:
	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;

	static Logger& instance()
	{
		static Logger l;
		return l;
	}

	void LogInfo(std::string const& text);
	void LogWarning(std::string const & text);
	void LogError(std::string const & text);

private:
	Logger();

	#ifdef _WIN32
		HANDLE winCmdHandler;
	#endif

	mutable std::mutex mutex;
};

#define LOG_INFO(text) sc::Logger::instance().LogInfo(text);
#define LOG_WARNING(text) sc::Logger::instance().LogWarning(text);	
#define LOG_ERROR(text) sc::Logger::instance().LogError(text);
} // namespace sc