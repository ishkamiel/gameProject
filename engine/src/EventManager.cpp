#include "EventManager.h"

#include <assert.h>

#include <algorithm>

namespace pdEngine
{
	EventManager::EventManager()
	: eventListeners(), eventQueueIn(), eventQueueOut()
	{}

	void EventManager::fireEvent(EventID id, EventData eventData)
	{
        //auto pair = std::make_pair<EventID, EventData>(id, eventData);
		eventQueueIn->push({id, eventData});
	}

	void EventManager::onUpdate(TimeDelta timeDelta)
	{
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

	EventListener::EventListener(EventManager* em, EventID id, ListenerFunction_wptr listener)
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
