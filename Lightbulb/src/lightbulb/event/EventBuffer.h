#pragma once
#include "lbpch.h"

#include "Event.h"

namespace event
{
	class EventBuffer
	{
	public:
		void fireEvent(std::shared_ptr<Event>& event);
		bool hasEvents() { return eventBuffer.size(); }
		std::shared_ptr<Event> nextEvent();

	private:
		std::queue<std::shared_ptr<Event>> eventBuffer;
	};
}


