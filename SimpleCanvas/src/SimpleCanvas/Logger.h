#pragma once

#include "Core.h"

namespace sc
{
class Logger
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
	void LogOk(const char * format, ...);

private:
	Logger();
	~Logger();
};

// for define vargs "##" means, if there will be no vards, comma will be removed
#ifdef BUILD_TYPE_DEBUG
	#define LOG_INFO(format, ...) sc::Logger::instance().LogInfo(format, ##__VA_ARGS__);
	#define LOG_WARNING(format,  ...) sc::Logger::instance().LogWarning(format, ##__VA_ARGS__);
	#define LOG_ERROR(format, ...) sc::Logger::instance().LogError(format, ##__VA_ARGS__);
	#define LOG_OK(format, ...) sc::Logger::instance().LogOk(format, ##__VA_ARGS__);
#else
	#define LOG_INFO(format, ...)
	#define LOG_WARNING(format,  ...)
	#define LOG_ERROR(format, ...)
	#define LOG_OK(format, ...)
#endif
} // namespace sc