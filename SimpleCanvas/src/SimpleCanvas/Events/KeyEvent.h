#pragma once

#include "Event.h"

namespace sc {

class SC_API KeyEvent : public Event
{
public:
	inline int GetKeyCode() const { return keyCode; }

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	KeyEvent(int pKeyCode) : keyCode(pKeyCode) {}

	int keyCode;
};


class SC_API KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(int pKeyCode, int pRepeatCount)
		: KeyEvent(pKeyCode), repeatCount(pRepeatCount) {}

	inline int GetRepearCount() const { return repeatCount; }

	std::string ToString() const override
	{
		std::string result = "KeyPressedEvent: " + std::to_string(keyCode) + " (" + std::to_string(repeatCount) + " repeats)";
		return result;
	}

	EVENT_CLASS_TYPE(KeyPressed)

private:
	int repeatCount;
};

class SC_API KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(int pKeyCode) : KeyEvent(pKeyCode) {}

	std::string ToString() const override
	{
		std::string result = "KeyReleasedEvent: " + std::to_string(keyCode);
		return result;
	}

	EVENT_CLASS_TYPE(KeyReleased)
};
}