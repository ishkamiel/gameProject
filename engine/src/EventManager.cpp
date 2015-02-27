#include "EventManager.h"

#include <assert.h>

namespace pdEngine
{
	EventManager::EventManager()
	: eventListeners()
	{}

	void EventManager::fireEvent(const EventID id, const EventData eventData)
	{
		eventQueueIn->push(std::make_pair<EventID,EventData>(id, eventData));
	}

	void EventManager::onUpdate(TimeDetla timeDelta) override
	{
		eventQueueIn.swap(eventQueueOut);

		/*
		auto list = eventListeners.find(id);

		if (list == eventListeners.end())
		{
			return(0); // no registered listeners for event
		}

		auto listenersCalled = 0;

		for (auto listener = list->second->begin(); listener != list->second->end(); list++)
		{
			if (! (*listener)(eventData))
			{
				return(++listenersCalled);
			}
			++listenersCalled;
		}
		*/
	}

	EventListenerUniquePtr EventManager::createEventListener(EventID eventID, EventListenerDelegate eld)
	{
	}

	void EventManager::addListener(const EventID id, const EventListenerDelegate delegate)
	{
		auto list = eventListeners[id];
		list.push_back(delegate);
	}

	void EventManager::removeListener(const EventID id, const EventListenerDelegate delegate)
	{
		auto foundList = eventListeners.find(id);

		if (foundList == eventListeners.end())
			return;

		auto list = foundList->second;

		for (auto i = list.begin(); i != list.end(); i++)
		{
			if (*i = delegate)
			{
				list.erase(i);
				return;
			}
		}
	}

	/*
	 * EventListener
	 */

	EventListener::EventListener(EventManagerSharedPtr em, EventID id, EventListenerDelegate delegate)
	: eventManager(em), eventID(id), delegate(delegate)
	{
		assert(delegate != nullptr);
		eventManager->addListener(id, delegate);
	}

	EventListener::~EventListener()
	{
		cancel();
	}

	void EventListener::cancel()
	{
		if (eventManager != nullptr)
		{
			eventManager->removeListener(eventID, delegate);
			eventManager.reset();
		}
	}

	const EventID EventListener::getEventID() const
	{
		return(eventID);
	}
}
