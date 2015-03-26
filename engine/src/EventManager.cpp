#include "EventBasic.h"
#include "EventManager.h"
#include "Logger.h"

#include <cassert>
#include <algorithm>
#include <memory>

namespace pdEngine
{
    EventManager::EventManager()
    {}

    EventManager::EventManager(TimeDelta updateInterval)
        : updateInterval(updateInterval)
    {}

    EventManager::~EventManager()
    {
        //TODO Do we need to clean something up?
    }

    void EventManager::onInit()
    {
        //TODO Do we need to so something?
    }

    void EventManager::onUpdate(TimeDelta timeDelta)
    {
        (void)timeDelta;
        //DLOG("EventManager onUpdate");

        if (eventQueueIn.size() == 0) return;
        auto log = GET_LOGGER();
        log->debug("EventManager processinging queued events");

        std::swap(eventQueueIn, eventsProcessing);

        while (eventsProcessing.size() > 0)
        {
            auto data = eventsProcessing.front();
            eventsProcessing.pop();

            assert(data != nullptr);
            log->debug("Processing event of type {}", data->getTypeID());

            auto list = findEventList(data->getTypeID());
            if (list != nullptr) 
            {
                log->debug("Found {} listeners", list->size());

                for (auto i : *list)
                {
                    log->debug("Trying to call listener");
                    i(data);
                }
            }
        }
    }

    void EventManager::queueEvent(const EventTypeID id)
    {
        DLOG("Queing event based on EventTypeID: {0}", id);
        auto ptr = std::make_shared<EventBasic>(id);
        DLOG("ptr made, queque size is: {0}", eventQueueIn.size());

        DLOG("Still okay {0}", eventQueueIn.size());

        eventQueueIn.size();
        //assert(eventQueueIn != nullptr);
        //eventQueueIn.push(std::make_shared<EventBasic>(id));
        eventQueueIn.push(ptr);
        DLOG("okay");

    }

    void EventManager::queueEvent(const Event_sptr eventPtr)
    {
        DLOG("Queing new event EventTypeID: {0}", eventPtr->getTypeID());
        eventQueueIn.push(eventPtr);
    }

    void EventManager::addListener(
            const EventTypeName eventName, 
            EventListener listener)
    {
        addListener(getEventID(eventName), listener);
    }

    void EventManager::addListener(
            const EventTypeID eventID,
            EventListener listener)
    {
        auto log = GET_LOGGER();

        auto list = findEventList(eventID, true);
        assert(list != nullptr);

        list->push_back(listener);
        assert(list->size() != 0);
        assert(list->size() == eventMap[eventID]->size());

        log->debug("Added listener for event, EventTypeID {}", eventID, "\n");
    }

    EventListenerList* EventManager::findEventList(EventTypeID id, bool create)
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

    EventManager_sptr getEventManager()
    {
        static EventManager_sptr em {}; //= std::make_shared<EventManager>();
        return em;
    }
}
