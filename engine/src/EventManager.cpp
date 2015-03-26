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
        eventQueueIn.push(std::make_shared<EventBasic>(id));
    }

    void EventManager::queueEvent(const Event_sptr eventDataPtr)
    {
        eventQueueIn.push(eventDataPtr);
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

    // void EventManager::removeListener(
    //         const EventTypeID id, 
    //         EventListener listener)
    // {
    //     auto f = eventMap.find(id);
    //     if (f == eventMap.end()) return;
    //
    //     auto list = f->second;
    //
    //     //listener.reset();
    //
    //     //TODO check on weak_ptr == shared_ptr comparison.
    //
    //     //this is kinda useless since we only do a search for expired weak
    //     //pointer, which is useless while we hold a corresponding shared_ptr 
    //
    //     auto iterator = list.begin();
    //     while (iterator != list.end())
    //     {
    //         if (iterator->expired())
    //             list.erase(iterator++);
    //         else 
    //             ++iterator;
    //     }
    // }

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
        static EventManager_sptr em = std::make_shared<EventManager>();
        return em;
    }
}
