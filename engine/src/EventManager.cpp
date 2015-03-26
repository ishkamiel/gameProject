#include "EventManager.h"
#include "Logger.h"

#include <assert.h>
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

        std::swap(eventQueueIn, eventQueueOut);

        while (eventQueueOut.size() > 0)
        {
            auto data = eventQueueOut.front();
            eventQueueIn.pop();

            auto f = eventMap.find(data->getEventTypeID());
            if (f == eventMap.end()) continue;

            auto list = f->second;
            auto iterator = list.begin();

            while (iterator != list.end())
            {
                if (iterator->expired())
                {
                    list.erase(iterator++);
                    continue;
                }
                (*iterator->lock())(data);
                ++iterator;
            }
        }
    }

    void EventManager::queueEvent(const EventData_sptr eventDataPtr)
    {
        eventQueueIn.push(eventDataPtr);
    }

    void EventManager::addListener(
            const EventTypeName eventName, 
            EventListener_sptr listener)
    {
        addListener(getEventID(eventName), listener);
    }

    void EventManager::addListener(
            const EventTypeID eventID,
            EventListener_sptr listener)
    {
        auto list = eventMap[eventID];

        list.push_back(listener);
    }

    void EventManager::removeListener(
            const EventTypeID id, 
            EventListener_sptr listener)
    {
        auto f = eventMap.find(id);
        if (f == eventMap.end()) return;

        auto list = f->second;

        listener.reset();

        //TODO check on weak_ptr == shared_ptr comparison.

        //this is kinda useless since we only do a search for expired weak
        //pointer, which is useless while we hold a corresponding shared_ptr 

        auto iterator = list.begin();
        while (iterator != list.end())
        {
            if (iterator->expired())
                list.erase(iterator++);
            else 
                ++iterator;
        }
    }

    EventManager_sptr getEventManager()
    {
        static EventManager_sptr em = std::make_shared<EventManager>();
        return em;
    }
}
