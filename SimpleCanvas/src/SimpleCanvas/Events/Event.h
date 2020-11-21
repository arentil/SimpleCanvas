#pragma once

#include "../../stdafx.h"
#include "../Core.h"

namespace sc {
enum class EventType
{
	None = 0,
	// ******* WINDOW *******
	WindowClose,
	WindowResize,
	WindowFocus,
	WindowLostFocus,
	WindowMoved,
	// ******* TICK/UPDATE/RENDER *******
	AppTick,
	AppUpdate,
	AppRender,
	// ******* KEYS *******
	KeyPressed,
	KeyReleased,
	// ******* MOUSE *******
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

	inline bool isHandled() const { return handled; }

private:
	int category;
	bool handled;
};

class FunctionHandler
{
public:
	void call(Event &event)
	{
		exec(event);
	}

private:
	virtual void exec(Event &event) = 0;
};

template<typename T, typename EventType>
class MemberFunctionHandler : public FunctionHandler
{
public:
	using MemberFunction = void (T::*)(EventType&);

	MemberFunctionHandler(T* pInstance, MemberFunction pFunction)
		: instance(pInstance), function(pFunction) {}

	void exec(Event &event) override
	{
		(instance->*function)(static_cast<EventType&>(event));
	}

private:
	T* instance;
	MemberFunction function;
};

class EventDispatcher
{
public:
	using Callbacks = std::vector<std::unique_ptr<FunctionHandler>>;

	template<typename T, typename EventType>
	void subscribe(T* pInstance, void (T::*pFunction)(EventType&))
	{
		callbacks[EventType::staticType()].emplace_back(new MemberFunctionHandler<T, EventType>(pInstance, pFunction));
	}

	void dispatch(Event &event)
	{
		if (callbacks[event.type()].empty())
			return;

		for (auto &callback : callbacks[event.type()])
			callback->call(event);

		callbacks.erase(event.type());	// pointers to FunctionHandler objects will be self deleted
	}

private:
	std::map<EventType, Callbacks> callbacks;
};

} // namespace sc
