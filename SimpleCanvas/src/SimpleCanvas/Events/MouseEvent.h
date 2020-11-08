#pragma once

#include "Event.h"


namespace simpleCanvas {

	class SC_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : mouseX(x), mouseY(y) {}

		inline float GetX() const { return mouseX; }
		inline float GetY() const { return mouseY; }

		std::string ToString() const override
		{
			std::string result = "MouseMovedEvent: " + std::to_string(mouseX) + ", " + std::to_string(mouseY);
			return result;
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float mouseX, mouseY;
	};

	class  SC_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : x_offset(xOffset), y_offset(yOffset) {}

		inline float GetXOffset() const { return x_offset; }
		inline float GetYOffset() const { return y_offset; }

		std::string ToString() const override
		{
			std::string result = "MouseScrolledEvent: " + std::to_string(x_offset) + ", " + std::to_string(y_offset);
			return result;
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float x_offset, y_offset;
	};


	class SC_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return _button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : _button(button) {}

		int _button;
	};

	class SC_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::string result = "MouseButtonPressedEvent: " + std::to_string(_button);
			return result;
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class SC_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::string result = "MouseButtonPressedEvent: " + std::to_string(_button);
			return result;
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}