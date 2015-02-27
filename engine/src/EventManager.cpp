#include "EventManager.h"

#include <assert.h>

namespace pdEngine
{
	EventManager::EventManager()
	: eventListeners()
	{}

	int EventManager::fireEvent(const EventID id, const EventData& eventData)
	{
		auto list = eventListeners.find(id);

		if (list == eventListeners.end())
			return(0); // no registered listeners for event

		auto listenersCalled = 0;
		for (auto listener = list->second->begin(); listener != list->second->end(); list++)
		{
			if (! (*listener)(eventData))
			{
				return(++listenersCalled);
			}
			++listenersCalled;
		}

		return(listenersCalled);
	}

	EventListenerUniquePtr EventManager::createEventListener(EventID eventID, EventListenerDelegate eld)
	{
	}

	void EventManager::addListener(const EventID id, const EventListenerDelegate delegate)
	{
		auto list = eventListeners[id];
		list->push_back(delegate);
	}

	void EventManager::removeListener(const EventID id, const EventListenerDelegate delegate)
	{
		auto foundList = eventListeners.find(id);

		if (foundList == eventListeners.end())
			return;

		auto foundDelegate = foundList->second->find(delegate);

		if (foundDelegate == foundDelegate->second->end())
			return; // hmm, cannot find delegate

		foundList->second->erase(foundDelegate);
	}

	/*
	 * EventListener
	 */

	EventListener::EventListener(EventManagerSharedPtr em, EventID id, EventListenerDelegate delegate)
	: eventManager(em), eventID(id), delegate(delegate)
	{
		assert(delegate != nullptr);
		//assert(eventManager != nullptr && delegate != nullptr);
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
			// FIXME need to fix this once FastDelegate stuff is added.
			//delete delegate;
		}
	}

	const EventID EventListener::getEventID() const
	{
		return(eventID);
	}
}
