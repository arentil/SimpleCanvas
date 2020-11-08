#pragma once

#include "Core.h"

namespace sc {
class SC_API Application
{
public:
	Application();
	virtual ~Application();

	void run();
};

// to be defined in client
Application *CreateApplication();
}

