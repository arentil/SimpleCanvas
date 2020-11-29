#pragma once

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

	void LogInfo(const char * format, ...);
	void LogWarning(const char * format, ...);
	void LogError(const char * format, ...);

private:
	Logger();
};

// for define vargs "##" means, if there will be no vards, comma will be removed
#define LOG_INFO(format, ...) sc::Logger::instance().LogInfo(format, ##__VA_ARGS__);
#define LOG_WARNING(format,  ...) sc::Logger::instance().LogWarning(format, ##__VA_ARGS__);	
#define LOG_ERROR(format, ...) sc::Logger::instance().LogError(format, ##__VA_ARGS__);
} // namespace sc