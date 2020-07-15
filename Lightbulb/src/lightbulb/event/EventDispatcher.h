#pragma once

#include "Event.h"
#include "WindowEvents.h"

namespace event
{
	#define EVENT_BIND_FUNC(func) std::bind(&func, this, std::placeholders::_1)

	class EventDispatcher
	{
	public:
		EventDispatcher(std::shared_ptr<Event>& evt)
			:evt(evt)
		{}

		/* U - The type of Event
		*  F - The binded function to call
		*  When runnng becomes if eventype matches U (which has been substituted in)
		*  call func((U)evt) - U not U& as function definition is not by reference
		*/
		template<typename U, typename F>
		void dispatch(const F& func)
		{
			if (evt->getEventType() == U::getStaticType())
			{
				func(std::static_pointer_cast<U>(evt));
			}
		}

	private:
		std::shared_ptr<Event> evt;
	};
}
