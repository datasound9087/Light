#pragma once

#include "Event.h"
#include "Keys.h"

namespace event
{
	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double xOffset, double yOffset)
			: xOffset(xOffset), yOffset(yOffset)
		{}
		virtual ~MouseScrolledEvent() {}

		double getXOffset() const { return xOffset; }
		double getYOffset() const { return yOffset; }

		REGISTER_EVENT_TYPE(EventType::MouseScrolled)
		REGISTER_EVENT_CATEGORY(EventCategory::Mouse)

	private:
		double xOffset;
		double yOffset;
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double xPos, double yPos)
			: xPos(xPos), yPos(yPos)
		{}
		virtual ~MouseMovedEvent() {}

		double getXPos() const { return xPos; }
		double getYPos() const { return yPos; }

		REGISTER_EVENT_TYPE(EventType::MouseMoved)
		REGISTER_EVENT_CATEGORY(EventCategory::Mouse)

	private:
		double xPos;
		double yPos;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int key, uint8_t mods)
			:key(key), modifiers(mods)
		{}

		int getKey() const { return key; }
		uint8_t getModifiers() const { return modifiers; }

	protected:
		int key;
		uint8_t modifiers;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int key, uint8_t mods)
			:MouseButtonEvent(key, mods)
		{}
		virtual ~MouseButtonPressedEvent() {}
		bool isButtonPressed(int key) { return this->key == key; }
		bool areModifiersPressed(uint8_t bitmask) { return bitmask & modifiers; }

		REGISTER_EVENT_TYPE(EventType::MouseButtonPressed)
		REGISTER_EVENT_CATEGORY(EventCategory::Mouse)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int key, uint8_t mods)
			:MouseButtonEvent(key, mods)
		{}
		virtual ~MouseButtonReleasedEvent() {}

		REGISTER_EVENT_TYPE(EventType::MouseButtonReleased)
		REGISTER_EVENT_CATEGORY(EventCategory::Mouse)
	};
}
