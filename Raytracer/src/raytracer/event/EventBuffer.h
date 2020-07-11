#pragma once
#include "rtpch.h"

#include "Event.h"

namespace event
{
	class EventBuffer
	{
	public:
		void fireEvent(std::unique_ptr<Event>& event);
		bool hasEvents() { return eventBuffer.size(); }
		std::unique_ptr<Event> nextEvent();

	private:
		std::queue<std::unique_ptr<Event>> eventBuffer;
	};
}


