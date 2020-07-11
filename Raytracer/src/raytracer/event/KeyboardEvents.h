#pragma once

#include "Event.h"
#include "Keys.h"

namespace event
{
	class KeyboardEvent : public Event
	{
	public:
		KeyboardEvent(int key, uint8_t mods)
			:key(key), modifiers(mods)
		{}

		int getKey() const { return key; }
		uint8_t getModifiers() const { return modifiers; }
	
	protected:
		int key;
		uint8_t modifiers;
	};

	class KeyboardPressedEvent : public KeyboardEvent
	{
	public:
		KeyboardPressedEvent(int key, uint8_t mods)
			:KeyboardEvent(key, mods)
		{}
		virtual ~KeyboardPressedEvent() {}
		bool isKeyPressed(int key) { return this->key == key; }
		bool areModifiersPressed(uint8_t bitmask) { return bitmask & modifiers; }

		REGISTER_EVENT_TYPE(EventType::KeyPressed)
		REGISTER_EVENT_CATEGORY(EventCategory::Keyboard)
	};

	class KeyboardReleasedEvent : public KeyboardEvent
	{
	public:
		KeyboardReleasedEvent(int key, uint8_t mods)
			:KeyboardEvent(key, mods)
		{}
		virtual ~KeyboardReleasedEvent() {}
		
		REGISTER_EVENT_TYPE(EventType::KeyReleased)
		REGISTER_EVENT_CATEGORY(EventCategory::Keyboard)
	};

	class KeyboardTypedEvent : public Event
	{
	public:
		KeyboardTypedEvent(uint32_t codePoint)
			:codePoint(codePoint)
		{}
		virtual ~KeyboardTypedEvent() {}
		uint32_t getCodePoint() const { return codePoint; }

		REGISTER_EVENT_TYPE(EventType::KeyTyped)
		REGISTER_EVENT_CATEGORY(EventCategory::Keyboard)

	private:
		uint32_t codePoint;
	};
}

