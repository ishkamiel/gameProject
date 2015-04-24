#pragma once

#include "events/EventManager.h"
#include "events/ListenerHandle.h"
#include "tasks/Task.h"

#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>

namespace pdEngine {

class EventManagerImpl : public EventManager {
    using ListenerList = std::vector<std::weak_ptr<ListenerHandle>>;
    using EventMap = std::map<EventTypeID, ListenerList*>;
    //using EventMapPair = std::pair<EventTypeID, EventListenerList*>;
    using EventQueue = std::queue<Event_sptr>;

    EventMap eventMap{};
    EventQueue eventQueueIn{};
    EventQueue eventsProcessing{};
    std::unordered_set<EventTypeID> m_cleanupList {};

public:
    EventManagerImpl();
    virtual ~EventManagerImpl();

    std::string v_getTaskName(void) const noexcept override { return "Event Manager"; }


    void onUpdate(int deltaMs) noexcept override;

    void queueEvent(const Event_sptr) noexcept override;
    void queueEvent(const EventTypeID) noexcept override;

    ListenerHandle_sptr addListener(const EventTypeID&, EventListener) noexcept override;

    // disable making of copies
    EventManagerImpl(const EventManagerImpl&) = delete;
    EventManagerImpl& operator=(const EventManagerImpl&) = delete;
};

}
