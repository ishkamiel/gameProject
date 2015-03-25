#include "EventListener.h"

namespace pdEngine
{
	EventListener::EventListener(
            EventManager* em, 
            EventID id, 
            ListenerFunction_wptr listener)
	: eventManager(em), eventID(id), listenerFunction(listener)
	{}

	EventListener::~EventListener()
	{
		cancel();
	}

	void EventListener::cancel()
	{
        auto l = listenerFunction.lock();
        if (l)
        {
			eventManager->removeListener(eventID, l);
            l.reset();
		}
        listenerFunction.reset();
	}

	EventID EventListener::getEventID() const
	{
		return(eventID);
	}
}
