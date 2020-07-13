#pragma once
#include "rtpch.h"

namespace event
{
	enum class EventType
	{
		None = 0,
		WindowFocusLost, WindowFocusGained, WindowMoved, WindowResized, WindowClosed,
		MouseScrolled, MouseMoved, MouseButtonPressed, MouseButtonReleased,
		KeyPressed, KeyReleased, KeyTyped
	};

	enum class EventCategory
	{
		None = 0,
		Keyboard,
		MouseButton,
		Mouse,
		Window
	};

#define REGISTER_EVENT_TYPE(type) static EventType getStaticType() { return type; } \
								virtual EventType getEventType() const override { return getStaticType(); } \
								virtual const std::string& getName() const override { return #type; }

#define REGISTER_EVENT_CATEGORY(category) EventCategory getEventCategory() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;
		virtual EventType getEventType() const = 0;
		virtual EventCategory getEventCategory() const = 0;
		virtual const std::string& getName() const = 0;
	};
}
