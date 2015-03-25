#include "EventManager.h"

#include "Logger.h"

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


    void EventManager::onUpdate(TimeDelta timeDelta)
    {
        (void)timeDelta;

        std::swap(eventQueueIn, eventQueueOut);

        while (eventQueueOut.size() > 0)
        {
            EventData& data = eventQueueOut.pop();

            auto f = eventMap.find(data.getEventTypeID());
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

    void EventManager::queueEvent(const EventData& eventData)
    {
        eventQueueIn.push(eventData);
    }

    void EventManager::addListener(
            const EventTypeName& eventName, 
            EventListener_sptr listener)
    {
        addListener(getEventID(eventName), listener);
    }

    void EventManager::addListener(
            const EventTypeID& eventID,
            EventListener_sptr listener)
    {
        auto list = eventMap[eventID];

        list.push_back(listener);
    }

    void EventManager::removeListener(
            const EventTypeID& id, 
            EventListener_sptr listener)
    {
        auto f = eventMap.find(id);
        if (f == eventMap.end()) return;

        auto list = f->second;
        std::remove(list.begin(), list.end(), listener);
    }
}
