#pragma once

#include "Event.h"

namespace event
{
	class WindowFocusLostEvent : public Event
	{
	public:
		virtual ~WindowFocusLostEvent() {}

		REGISTER_EVENT_TYPE(EventType::WindowFocusLost)
		REGISTER_EVENT_CATEGORY(EventCategory::Window)
	};

	class WindowFocusGainedEvent : public Event
	{
	public:
		virtual ~WindowFocusGainedEvent() {}

		REGISTER_EVENT_TYPE(EventType::WindowFocusLost)
		REGISTER_EVENT_CATEGORY(EventCategory::Window)
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(int xPos, int yPos)
			: xPos(xPos), yPos(yPos)
		{}
		virtual ~WindowMovedEvent() {}

		int getXPos() const { return xPos; }
		int getYPos() const { return yPos; }

		REGISTER_EVENT_TYPE(EventType::WindowMoved)
		REGISTER_EVENT_CATEGORY(EventCategory::Window)

	private:
		int xPos;
		int yPos;
	};

	class WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(int width, int height)
			: width(width), height(height)
		{}
		virtual ~WindowResizedEvent() {}

		int getWidth() const { return width; }
		int getHeight() const { return height; }

		REGISTER_EVENT_TYPE(EventType::WindowResized)
		REGISTER_EVENT_CATEGORY(EventCategory::Window)

	private:
		int width;
		int height;
	};

	class WindowClosedEvent : public Event
	{
	public:
		virtual ~WindowClosedEvent() {}

		REGISTER_EVENT_TYPE(EventType::WindowClosed)
		REGISTER_EVENT_CATEGORY(EventCategory::Window)
	};
}
