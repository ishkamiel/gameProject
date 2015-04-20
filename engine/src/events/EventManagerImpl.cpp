#include "events/DefaultEvent.h"
#include "events/EventManagerImpl.h"
#include "Logger.h"
#include "Utils.h"

#include <cassert>
#include <algorithm>
#include <memory>

namespace pdEngine
{
    EventManagerImpl::EventManagerImpl()
    {}

    EventManagerImpl::~EventManagerImpl()
    {
        //TODO Do we need to clean something up?
    }


    void EventManagerImpl::onUpdate(int deltaMs) noexcept
    {
        (void)deltaMs;

        if (eventQueueIn.size() == 0) return;
        auto log = getLogger();
        log->debug("EventManager processing queued events");

        std::swap(eventQueueIn, eventsProcessing);

        while (eventsProcessing.size() > 0)
        {
            auto data = eventsProcessing.front();
            eventsProcessing.pop();

            assert(data != nullptr);
            PD_debug("Processing event of type {}", data->getTypeID());
			auto listeners_called = 0;

            auto list = findEventList(data->getTypeID());
            if (list != nullptr) 
            {
                log->debug("Found {} listeners", list->size());

                for (auto i : *list)
                {
                    log->debug("Trying to call listener");
                    i(data);
					++listeners_called;
                }
            }
            PD_debug("Event processed by {0} listeners", listeners_called);
        }
    }

    void EventManagerImpl::queueEvent(const EventTypeID id)
    {
        eventQueueIn.push(std::make_shared<DefaultEvent>(id));
    }

    void EventManagerImpl::queueEvent(const Event_sptr eventPtr)
    {
        PD_debug("Queing new event EventTypeID: {0}", eventPtr->getTypeID());
        eventQueueIn.push(eventPtr);
    }

    /*
    void EventManager::addListener( const EventTypeName eventName, EventListener listener)
    {
        addListener(getEventID(eventName), listener);
    }
    */

    void EventManagerImpl::addListener(
            const EventTypeID eventID,
            EventListener listener)
    {
        auto log = getLogger();

        auto list = findEventList(eventID, true);
        assert(list != nullptr);

        list->push_back(listener);
        assert(list->size() != 0);
        assert(list->size() == eventMap[eventID]->size());

        log->debug("Added listener for event, EventTypeID {}", eventID, "\n");
    }

	auto EventManagerImpl::findEventList(EventTypeID id, bool create)
		-> EventListenerList*
    {
        auto f = eventMap.find(id);
        if (f == eventMap.end()) 
        {
            if (create)
            {
                eventMap.insert(EventMapPair(id, new EventListenerList()));
                return findEventList(id);
            }
            return nullptr;
        }

        return f->second;
    }
}
