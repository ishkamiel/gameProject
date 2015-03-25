#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "Events.h"
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
    using EventDataQueue = std::queue<EventData>;

    class EventManager : public Task
    {
        std::map<EventTypeID, EventListenerList> eventMap {};
        EventDataQueue eventQueueIn {};
        EventDataQueue eventQueueOut {};

    public:
        EventManager();
        ~EventManager();

        void onUpdate(TimeDelta) override;

        void queueEvent(const EventData&);

        void addListener(const EventTypeName&, EventListener_sptr);
        void addListener(const EventTypeID&, EventListener_sptr);
        void removeListener(const EventTypeID&, EventListener_sptr);
    };
}

#endif

