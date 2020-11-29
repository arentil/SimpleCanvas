#include "Logger.h"

#include <ctime>
#include <chrono>
#include <thread>
#include <cstdarg>

namespace sc {
namespace {
enum class CONSOLE_TEXT_COLOR : int
{
	COLOR_ERROR = 12,
	COLOR_WARNING = 14,
	COLOR_INFO = 15
};

std::chrono::system_clock::duration duration_since_midnight() {
	auto now = std::chrono::system_clock::now();

	time_t tnow = std::chrono::system_clock::to_time_t(now);
	tm *date = std::localtime(&tnow);
	date->tm_hour = 0;
	date->tm_min = 0;
	date->tm_sec = 0;
	auto midnight = std::chrono::system_clock::from_time_t(std::mktime(date));

	return now - midnight;
}

std::string getCurrentTime()
{
	auto since_midnight = duration_since_midnight();
	auto hours = std::chrono::duration_cast<std::chrono::hours>(since_midnight);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(since_midnight - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(since_midnight - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(since_midnight - hours - minutes - seconds);

	std::string hoursStr = (hours.count() < 10 ? "0" : "") + std::to_string(hours.count());
	std::string minutesStr = (hours.count() < 10 ? "0" : "") + std::to_string(minutes.count());
	std::string secondsStr = (hours.count() < 10 ? "0" : "") + std::to_string(seconds.count());
	std::string millisecondsStr = std::to_string(milliseconds.count()) + (milliseconds.count() < 10 ? "0" : "") + (milliseconds.count() < 100 ? "0" : "");

	return (hoursStr + ":" + minutesStr + ":" + secondsStr + "." + millisecondsStr);
}

void formatColorConsole(CONSOLE_TEXT_COLOR color)
{
	switch (color)
	{
		case CONSOLE_TEXT_COLOR::COLOR_WARNING:
			printf("\033[1;33m");
			break;
		case CONSOLE_TEXT_COLOR::COLOR_ERROR:
			printf("\033[1;31m");
			break;
		case CONSOLE_TEXT_COLOR::COLOR_INFO:
		default:
			break;
	}
}

#ifdef _WIN32
	#include <Windows.h>
	HANDLE winCmdHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	#define FORMAT_CONSOLE_BEGIN(color) SetConsoleTextAttribute(winCmdHandler, (int)color); \
		printf("[ %s ] ", getCurrentTime().c_str());

	#define FORMAT_CONSOLE_END printf("\n");
#else
	#define FORMAT_CONSOLE_BEGIN(color)					\
		printf("[ %s ] ", getCurrentTime().c_str());	\
		formatColorConsole(color);

	#define FORMAT_CONSOLE_END printf("\033[0m\n");
#endif

#define PRINT_ARGS			\
	va_list args;			\
	va_start(args, format);	\
	vprintf(format, args);	\
	va_end (args);
} // namespace

Logger::Logger()
{}

void Logger::LogInfo(const char* format, ...)
{
	FORMAT_CONSOLE_BEGIN(CONSOLE_TEXT_COLOR::COLOR_INFO);
	PRINT_ARGS
	FORMAT_CONSOLE_END
}

void Logger::LogWarning(const char* format, ...)
{
	FORMAT_CONSOLE_BEGIN(CONSOLE_TEXT_COLOR::COLOR_WARNING);
	PRINT_ARGS
	FORMAT_CONSOLE_END
}

void Logger::LogError(const char* format, ...)
{
	FORMAT_CONSOLE_BEGIN(CONSOLE_TEXT_COLOR::COLOR_ERROR);
	PRINT_ARGS
	FORMAT_CONSOLE_END
}
} // namespace sc