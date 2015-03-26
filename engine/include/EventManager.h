#ifndef PDENGINE_EVENTMANAGER_H_
#define PDENGINE_EVENTMANAGER_H_

#include "EventData.h"
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
    using EventListenerList = std::vector<EventListener_wptr>;
    using EventDataQueue = std::queue<EventData_sptr>;


    class EventManager : public Task
    {
        std::map<EventTypeID, EventListenerList> eventMap {};
        EventDataQueue eventQueueIn {};
        EventDataQueue eventQueueOut {};

    public:
        EventManager();
        EventManager(TimeDelta updateInterval);
        ~EventManager();

        void onInit() override;
        void onUpdate(TimeDelta) override;

        void queueEvent(const EventData_sptr);

        void addListener(const EventTypeName, EventListener_sptr);
        void addListener(const EventTypeID, EventListener_sptr);
        void removeListener(const EventTypeID, EventListener_sptr);

    private:
        TimeDelta updateInterval {10 };
        TimeDelta lastUpdate = { 0 };
    };

    EventManager_sptr getEventManager();
}

#endif /* PDENGINE_EVENTMANAGER_H_ */
