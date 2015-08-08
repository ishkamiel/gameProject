#pragma once

#include "events/EventTypeID.h"
#include "tasks/Task.h"
#include "utils/Deprecated.h"

#include <memory>

namespace pdEngine {
class EventManager;
using EventManager_sptr = std::shared_ptr<EventManager>;

class I_Event;
using Event_sptr = std::shared_ptr<I_Event>;

class ListenerHandle;
using ListenerHandle_sptr = std::shared_ptr<ListenerHandle>;

using EventListener = std::function<bool(Event_sptr)>;

class EventManager : public Task {
public:
    EventManager() {};
    virtual ~EventManager() {};

    /**
     * @brief Queue event for processing on next update.
     */
    virtual void queueEvent(const Event_sptr) noexcept = 0;
    virtual void queueEvent(I_Event *event) noexcept = 0;
    DEPRECATED(virtual void queueEvent(const EventTypeID) noexcept) = 0;

    /**
     * @brief Add listener for event type.
     */
    virtual ListenerHandle_sptr addListener(const EventTypeID&, EventListener) noexcept = 0;

    template<typename C, typename F>
    ListenerHandle_sptr addListener(const EventTypeID&, const C*, const F*) noexcept;

    /**
     * @brief Returns the global singleton EventManager.
     */
    static EventManager_sptr get() noexcept;

    // Disable copy constructor & copy assignement
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;
};


/***************************************************************************************************
 * Implementations
 */

template<typename C, typename F>
ListenerHandle_sptr EventManager::addListener(
    const EventTypeID& eventId, const C* obj, const F* func) noexcept
{
    return addListener(eventId, std::bind(func, obj, std::placeholders::_1));
}

}
