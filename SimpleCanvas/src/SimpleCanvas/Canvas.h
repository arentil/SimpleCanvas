#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace sc
{
// This will be used for application to render

class Canvas
{
public:
	Canvas() = default;

	// deltaTime in seconds
	virtual void update(float deltaTime) {};
	virtual void onEvent(Event &event) {};
};
} // namespace sc