#include "EventManager.h"

#include <assert.h>

#include <algorithm>

namespace pdEngine
{
	EventManager::EventManager()
	{}
	
	EventManager::~EventManager()
	{
		//TODO
	}

	void EventManager::fireEvent(EventID id, EventData eventData)
	{
        //auto pair = std::make_pair<EventID, EventData>(id, eventData);
		eventQueueIn.push({id, eventData});
	}

	void EventManager::onUpdate(TimeDelta timeDelta)
	{
        //TODO
        timeDelta--;
	}

	EventListener_uptr EventManager::createListener(EventID eventID, ListenerFunction eld)
	{
        auto l_ptr = std::make_shared<ListenerFunction>(eld);
		auto list = eventListeners[eventID];
		list.push_back(l_ptr);

        EventListener_uptr retval { new EventListener(this, eventID, l_ptr) };
        return retval;
	}

	void EventManager::removeListener(const EventID id, ListenerFunction_sptr listener)
	{
		auto foundList = eventListeners.find(id);

		if (foundList == eventListeners.end())
			return;

		auto list = foundList->second;
        std::remove(list.begin(), list.end(), listener);
	}

	/*
	 * EventListener
	 */
}
