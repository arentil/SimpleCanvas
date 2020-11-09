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

enum EventCategory
{
	None = 0x0,
	EventCategoryApplication = 0x1,
	EventCategoryInput = 0x2,
	EventCategoryKeyboard = 0x4,
	EventCategoryMouse = 0x8,
	EventCategoryMouseButton = 0x10,
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class SC_API Event
{
	friend class EventDispatcher;
public:
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	inline bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	}

protected:
	bool handled = false;
};

class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;
public:
	EventDispatcher(Event & pEvent)
		: event(pEvent) {}

	template<typename T>
	bool Dispatch(EventFn<T> func)
	{
		if (event.GetEventType() == T::GetStaticType())
		{
			event.handled = func(*(T*)&event);
			return true;
		}
		return false;
	}

private:
	Event &event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}
} // namespace sc
