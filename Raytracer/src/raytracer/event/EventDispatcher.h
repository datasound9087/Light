#pragma once

#include "Event.h"
#include "WindowEvents.h"

namespace event
{
	#define EVENT_BIND_FUNC(func) std::bind(&func, this, std::placeholders::_1)

	class EventDispatcher
	{
	public:
		EventDispatcher(std::unique_ptr<Event>& evt) 
			:evt(std::move(evt))
		{}

		/* U - The type of Event
		*  F - The binded function to call
		*  When runnng becomes if eventype matches U (which has been substituted in)
		*  call func((U)evt) - U not U& as function definition is not by reference
		*/
		template<typename U, typename F>
		void dispatch(const F& func)
		{
			if (evt != nullptr && evt->getEventType() == U::getStaticType())
			{
				func(staticCastPtr<U>(evt));
			}
		}

	private:

		template<typename D, typename B>
		std::unique_ptr<D> staticCastPtr(std::unique_ptr<B>& base)
		{
			return std::unique_ptr<D>(static_cast<D*>(base.release()));
		}

	private:
		std::unique_ptr<Event> evt;
	};
}
