#include "EventManager.h"

namespace pdEngine
{
	EventManager::EventManager()
	: eventListeners()
	{}

	int EventManager::fireEvent(EventID id, EventData eventData)
	{
		int listenersCalled = 0;
		auto list = eventListeners.find(id);

		if (list != eventListeners.end())
		{
			for (auto listener = list->second->begin(); listener != list->second->end(); list++)
			{
				if (! listener(eventData)) //FIXME
				{
					return(++listenersCalled);
				}
				++listenersCalled;
			}
		}

		return(listenersCalled);
	}

	EventListenerUniquePtr EventManager::createEventListener(EventID, EventListenerDelegate)
	{
	}

	EventListenerUniquePtr EventManager::createEventListener(EventList, EventListenerDelegate)
	{
	}

	void EventManager::addListener(const EventID, const EventListenerDelegate&)
	{
	}

	void EventManager::removeListener(const EventID, const EventListenerDelegate&)
	{
	}
}
