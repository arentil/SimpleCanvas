#pragma once

#include "Event.h"

namespace sc {
class SC_API KeyEvent : public Event
{
public:
	KeyEvent(int pKeyCode)
	: Event(EventCategoryKeyboard | EventCategoryInput) 
	, keyCode(pKeyCode) {}

	inline int getKeyCode() const { return keyCode; }

private:
	int keyCode;
};

class SC_API KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int pKeyCode, int pRepeatCount)
	: KeyEvent(pKeyCode), repeatCount(pRepeatCount) {}

	inline int getRepearCount() const { return repeatCount; }
	EventType type() const override { return EventType::KeyPressed; }

private:
	int repeatCount;
};

class SC_API KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int pKeyCode) : KeyEvent(pKeyCode) {}

	EventType type() const override { return EventType::KeyReleased; }
};
} // namespace sc