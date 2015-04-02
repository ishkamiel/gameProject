#ifndef PDENGINE_EVENTMANAGER_H_
#define PDENGINE_EVENTMANAGER_H_


#include "events/I_Event.h"
#include "events/EventManager.h"
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
    using EventListenerList = std::vector<EventListener>;
    using EventQueue = std::queue<Event_sptr>;

    class EventManagerImpl : public Task, public EventManager
    {
        using EventMap = std::map<EventTypeID, EventListenerList*>;
        using EventMapPair = std::pair<EventTypeID, EventListenerList*>;

        EventMap eventMap               {};
        EventQueue eventQueueIn         {};
        EventQueue eventsProcessing     {};
        TimeDelta updateInterval        { 10 };
        TimeDelta lastUpdate            { 0 };

    public:
        EventManagerImpl();
        ~EventManagerImpl();

        //void onInit() override;
        void onUpdate(TimeDelta) override;

        void queueEvent(const Event_sptr) override;
        void queueEvent(const EventTypeID) override;

        void addListener(const EventTypeID, EventListener) override;

    private:
        EventListenerList* findEventList(EventTypeID, bool = false);
    };
}

#endif /* PDENGINE_EVENTMANAGER_H_ */
