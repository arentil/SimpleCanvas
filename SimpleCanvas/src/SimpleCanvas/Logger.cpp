#include "Logger.h"

#include <ctime>
#include <chrono>
#include <thread>
#include <iostream>

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

#ifdef _WIN32
	#include <Windows.h>
	HANDLE winCmdHandler;

	void print(std::mutex &m, int color, std::string text)
	{
		std::lock_guard<std::mutex> guard(m);
		SetConsoleTextAttribute(winCmdHandler, color);
		std::cout << "[" << getCurrentTime() << "] " << text << std::endl;
	}
#else
	void print(std::mutex &m, int color, std::string text)
	{
		std::lock_guard<std::mutex> guard(m);
		std::string colorTagPrefix, colorTagSuffix;
		CONSOLE_TEXT_COLOR eColor = (CONSOLE_TEXT_COLOR)color;
		switch (eColor)
		{
			case CONSOLE_TEXT_COLOR::COLOR_INFO:
				break;
			case CONSOLE_TEXT_COLOR::COLOR_WARNING:
				colorTagPrefix = "\033[1;33m";
				colorTagSuffix = "\033[0m";
				break;
			case CONSOLE_TEXT_COLOR::COLOR_ERROR:
				colorTagPrefix = "\033[1;31m";
				colorTagSuffix = "\033[0m";
				break;
		}
		std::cout << "[" << getCurrentTime() << "] " << text << std::endl;
	}
#endif
} // namespace

Logger::Logger()
{}

void Logger::LogInfo(std::string const & text)
{
	std::thread t(print, std::ref(mutex), (int)CONSOLE_TEXT_COLOR::COLOR_INFO, std::ref(text));
	t.join();
}

void Logger::LogWarning(std::string const & text)
{
	std::thread t(print, std::ref(mutex), (int)CONSOLE_TEXT_COLOR::COLOR_WARNING, std::ref(text));
	t.join();
}

void Logger::LogError(std::string const & text)
{
	std::thread t(print, std::ref(mutex), (int)CONSOLE_TEXT_COLOR::COLOR_ERROR, std::ref(text));
	t.join();
}
} // namespace sc