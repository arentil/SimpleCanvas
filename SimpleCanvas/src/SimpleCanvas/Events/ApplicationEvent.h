#pragma once

#include "Event.h"

namespace sc {
class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(uint32_t pWidth, uint32_t pHeight) 
	: Event(EventCategory::EventCategoryApplication)
	, width(pWidth), height(pHeight) {}

	inline uint32_t getWidth() const { return width; }
	inline uint32_t getHeight() const { return height; }

	EventType type() const override { return EventType::WindowResize; }
	static EventType staticType() { return EventType::WindowResize; }

private:
	uint32_t width, height;
};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent()
	: Event(EventCategory::EventCategoryApplication) {}

	EventType type() const override { return EventType::WindowClose; }
	static EventType staticType() { return EventType::WindowClose; }
};

class AppTickEvent : public Event
{
public:
	AppTickEvent()
	: Event(EventCategory::EventCategoryApplication) {}

	EventType type() const override { return EventType::AppTick; }
	static EventType staticType() { return EventType::AppTick; }
};

class AppUpdateEvent : public Event
{
public:
	AppUpdateEvent()
	: Event(EventCategory::EventCategoryApplication) {}

	EventType type() const override { return EventType::AppUpdate; }
	static EventType staticType() { return EventType::AppUpdate; }
};

class AppRenderEvent : public Event
{
public:
	AppRenderEvent()
	: Event(EventCategory::EventCategoryApplication) {}

	EventType type() const override { return EventType::AppRender; }
	static EventType staticType() { return EventType::AppRender; }
};
} // namespace sc
