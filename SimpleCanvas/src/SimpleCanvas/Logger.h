#pragma once

#include "../stdafx.h"
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

	void Log(std::string const& text);

private:
	Logger() = default;

	mutable std::mutex mutex;
};

#define LOG_TEXT(text) sc::Logger::instance().Log(text);
}