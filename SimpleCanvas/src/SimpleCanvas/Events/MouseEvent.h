#pragma once

#include "Event.h"

namespace sc 
{
class MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(float x, float y) 
	: Event(EventCategoryMouse | EventCategoryInput)
	, mouseX(x), mouseY(y) {}

	inline float getX() const { return mouseX; }
	inline float getY() const { return mouseY; }

	EventType type() const override { return EventType::MouseMoved; }
	static EventType staticType() { return EventType::MouseMoved; }

private:
	float mouseX, mouseY;
};

class  MouseScrollEvent : public Event
{
public:
	MouseScrollEvent(float xOffset, float yOffset)
	: Event(EventCategoryMouse | EventCategoryInput)
	, x_offset(xOffset), y_offset(yOffset) {}

	inline float GetXOffset() const { return x_offset; }
	inline float GetYOffset() const { return y_offset; }

	EventType type() const override { return EventType::MouseScrolled; }
	static EventType staticType() { return EventType::MouseScrolled; }

private:
	float x_offset, y_offset;
};


class MouseButtonEvent : public Event
{
public:
	MouseButtonEvent(int pButton)
	: Event(EventCategoryMouse | EventCategoryInput)
	, button(pButton) {}

	inline int getMouseButton() const { return button; }

protected:
	int button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

	EventType type() const override { return EventType::MouseButtonPressed; }
	static EventType staticType() { return EventType::MouseButtonPressed; }
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

	EventType type() const override { return EventType::MouseButtonReleased; }
	static EventType staticType() { return EventType::MouseButtonReleased; }
};
} // namespace sc