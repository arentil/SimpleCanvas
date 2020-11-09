#include "Logger.h"

namespace sc {
namespace {
enum class CONSOLE_TEXT_COLOR : int
{
	COLOR_ERROR = 12,
	COLOR_WARNING = 14,
	COLOR_INFO = 15
};

void print(std::mutex &m, HANDLE &handle, CONSOLE_TEXT_COLOR color, std::string const & text)
{
	std::lock_guard<std::mutex> guard(m);
	SetConsoleTextAttribute(handle, (int)color);
	std::cout << text << std::endl;

}
} // namespace

Logger::Logger() : hConsole(GetStdHandle(STD_OUTPUT_HANDLE))
{}

void Logger::LogInfo(std::string const & text)
{
	std::thread t(print, std::ref(mutex), std::ref(hConsole), CONSOLE_TEXT_COLOR::COLOR_INFO, std::ref(text));
	t.join();
}

void Logger::LogWarning(std::string const & text)
{
	std::thread t(print, std::ref(mutex), std::ref(hConsole), CONSOLE_TEXT_COLOR::COLOR_WARNING, std::ref(text));
	t.join();
}

void Logger::LogError(std::string const & text)
{
	std::thread t(print, std::ref(mutex), std::ref(hConsole), CONSOLE_TEXT_COLOR::COLOR_ERROR, std::ref(text));
	t.join();
}

} // namespace sc