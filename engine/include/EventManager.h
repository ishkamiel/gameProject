#ifndef PDENGINE_EVENTMANAGER_H_
#define PDENGINE_EVENTMANAGER_H_

#include "Event.h"
#include "EventListener.h"
#include "Task.h"

#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>

namespace pdEngine
{
    class EventManager;
    using EventManager_sptr = std::shared_ptr<EventManager>;
    using EventListenerList = std::vector<EventListener>;
    using EventDataQueue = std::queue<Event_sptr>;


    class EventManager : public Task
    {
        using EventMapPair = std::pair<EventTypeID, EventListenerList*>;

        std::map<EventTypeID, EventListenerList*> eventMap {};
        EventDataQueue eventQueueIn {};
        EventDataQueue eventsProcessing {};
        TimeDelta updateInterval {10 };
        TimeDelta lastUpdate = { 0 };

    public:
        EventManager();
        EventManager(TimeDelta updateInterval);
        ~EventManager();

        void onInit() override;
        void onUpdate(TimeDelta) override;

        void queueEvent(const Event_sptr);
        void queueEvent(const EventTypeID);

        void addListener(const EventTypeName, EventListener);
        void addListener(const EventTypeID, EventListener);
        //void removeListener(const EventTypeID, EventListener);

    private:
        EventListenerList* findEventList(EventTypeID, bool = false);
    };

    EventManager_sptr getEventManager();
}

#endif /* PDENGINE_EVENTMANAGER_H_ */
