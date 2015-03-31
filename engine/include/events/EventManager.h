#ifndef PDENGINE_EVENTMANAGER_H_
#define PDENGINE_EVENTMANAGER_H_

#include "Timer.h"
#include "events/iEvent.h"
#include "events/EventListener.h"
#include "tasks/Task.h"

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
    using EventQueue = std::queue<Event_sptr>;

    static EventManager_sptr TheEventManager;

    class EventManager : public Task
    {
        using EventMap = std::map<EventTypeID, EventListenerList*>;
        using EventMapPair = std::pair<EventTypeID, EventListenerList*>;

        EventMap eventMap               {};
        EventQueue eventQueueIn         {};
        EventQueue eventsProcessing     {};
        TimeDelta updateInterval        { 10 };
        TimeDelta lastUpdate            { 0 };

    public:
        EventManager();
        EventManager(TimeDelta updateInterval);
        ~EventManager();

        void onInit() override;
        void onUpdate(TimeDelta) override;

        void queueEvent(const Event_sptr);
        void queueEvent(const EventTypeID);

        void addListener(const EventTypeID, EventListener);

    private:
        EventListenerList* findEventList(EventTypeID, bool = false);
    };
}

#endif /* PDENGINE_EVENTMANAGER_H_ */
