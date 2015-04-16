#pragma once

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

namespace pdEngine {

class EventManagerImpl : public Task, public EventManager {
    using EventListenerList = std::vector<EventListener>;
    using EventMap = std::map<EventTypeID, EventListenerList*>;
    using EventMapPair = std::pair<EventTypeID, EventListenerList*>;
    using EventQueue = std::queue<Event_sptr>;

    EventMap eventMap{};
    EventQueue eventQueueIn{};
    EventQueue eventsProcessing{};
    TimeDelta updateInterval{10};
    TimeDelta lastUpdate{0};

public:
    EventManagerImpl();
    ~EventManagerImpl();

    EventManagerImpl(const EventManagerImpl&) = delete;
    EventManagerImpl& operator=(const EventManagerImpl&) = delete;

    //void onInit() override;
    void onUpdate(TimeDelta) override;

    void queueEvent(const Event_sptr) override;
    void queueEvent(const EventTypeID) override;

    void addListener(const EventTypeID, EventListener) override;

private:
    EventListenerList* findEventList(EventTypeID, bool = false);
};

}
