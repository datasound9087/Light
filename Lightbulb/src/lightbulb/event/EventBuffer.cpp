#include "lbpch.h"
#include "EventBuffer.h"

namespace event
{

	void EventBuffer::fireEvent(std::shared_ptr<Event>& event)
	{
		eventBuffer.push(event);
	}

	std::shared_ptr<Event> EventBuffer::nextEvent()
	{
		auto evt = eventBuffer.front();
		eventBuffer.pop();
		return evt;
	}
}
