#include "Logger.h"

#include <iostream>

namespace sc {
	namespace {
		void print(std::mutex &m, std::string const & text)
		{
			std::lock_guard<std::mutex> guard(m);
			std::cout << text << std::endl;
		}
	}

	void Logger::Log(std::string const & text)
	{
		std::thread t(print, std::ref(mutex), std::ref(text));
		t.join();
	}

}