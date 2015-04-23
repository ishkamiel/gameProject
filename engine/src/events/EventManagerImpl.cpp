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

        PDE_DEBUG << "EventManager processing queued events";

        std::swap(eventQueueIn, eventsProcessing);

        while (eventsProcessing.size() > 0)
        {
            auto data = eventsProcessing.front();
            eventsProcessing.pop();

            assert(data != nullptr);
            PDE_DEBUG << "Processing event of type " << data->getTypeID();
			auto listeners_called = 0;

            auto list = findEventList(data->getTypeID());
            if (list != nullptr) 
            {
                PDE_DEBUG << "Found " << list->size() << " listeners";

                for (auto i : *list)
                {
                    PDE_DEBUG << "Trying to call listener";
                    i(data);
					++listeners_called;
                }
            }

            PDE_DEBUG << "Event processed by " << listeners_called << " listeners";
        }
    }

    void EventManagerImpl::queueEvent(const EventTypeID id)
    {
        eventQueueIn.push(std::make_shared<DefaultEvent>(id));
    }

    void EventManagerImpl::queueEvent(const Event_sptr eventPtr)
    {
        PDE_DEBUG << "Queing new event EventTypeID: " << eventPtr->getTypeID();
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

        auto list = findEventList(eventID, true);
        assert(list != nullptr);

        list->push_back(listener);
        assert(list->size() != 0);
        assert(list->size() == eventMap[eventID]->size());

        PDE_DEBUG << "Added listener for event, EventTypeID << " << eventID;
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
