#pragma once

#include "../../stdafx.h"
#include "../Core.h"

namespace sc {
enum class EventType
{
	None = 0,
	// Window Events
	WindowClose,
	WindowResize,
	WindowFocus,
	WindowLostFocus,
	WindowMoved,
	// App Events
	AppTick,
	AppUpdate,
	AppRender,
	// Key Events
	KeyPressed,
	KeyReleased,
	// Mouse Events
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMoved,
	MouseScrolled
};

// every category equals to toggled bit
enum EventCategory
{
	None = 0x0,
	EventCategoryApplication = 0x1,
	EventCategoryInput = 0x2,
	EventCategoryKeyboard = 0x4,
	EventCategoryMouse = 0x8,
	EventCategoryMouseButton = 0x10,
};

namespace {
std::string eventTypeNames[]{
	"None",
	"WindowClose",
	"WindowResize",
	"WindowFocus",
	"WindowLostFocus",
	"WindowMoved",
	"AppTick",
	"AppUpdate",
	"AppRender",
	"KeyPressed",
	"KeyReleased",
	"MouseButtonPressed",
	"MouseButtonReleased",
	"MouseMoved",
	"MouseScrolled"
};
}

class SC_API Event
{
	friend class EventDispatcher;
public:
	Event(int pCategory) : category(pCategory) {}
	virtual EventType type() const = 0;
	int getCategoryFlags() const { return category; };
	std::string name() const { return eventTypeNames[int(type())]; }

	inline bool isInCategory(EventCategory pCategory)
	{
		return category & pCategory;
	}

private:
	bool handled = false;
	int category;
};

class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;
public:
	EventDispatcher(Event & pEvent)
		: event(pEvent) {}

	template<typename T>
	bool dispatch(EventFn<T> func)
	{
		if (event.type() == T().type())
		{
			event.handled = func(*(T*)&event);
			return true;
		}
		return false;
	}

private:
	Event &event;
};

} // namespace sc
