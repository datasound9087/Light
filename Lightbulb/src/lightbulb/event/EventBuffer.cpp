#include "lbpch.h"
#include "EventBuffer.h"

namespace event
{

	void EventBuffer::fireEvent(std::unique_ptr<Event>& event)
	{
		eventBuffer.push(std::move(event));
	}
	std::unique_ptr<Event> EventBuffer::nextEvent()
	{
		auto evt = std::move(eventBuffer.front());
		eventBuffer.pop();
		return std::move(evt);
	}
}
