#pragma once

#include "events/EventTypeID.h"
#include "events/EventManager.h"
#include "events/I_Event.h"

#include <functional>
#include <string>

namespace pdEngine
{
using EventListener = std::function<bool(Event_sptr)>;

template<typename C, typename F>
EventListener createEventListener(C&, F&);

template<typename C, typename F>
EventListener listenToEvent(EventTypeID, C&&, F&&);

/*
 * Implementations
 */

template<typename C, typename F>
EventListener createEventListener(F& f, C& c)
{
    return std::bind(f, c, std::placeholders::_1);
}

/*
template<typename C, typename F>
EventListener listenToEvent(EventTypeID id, F& f, C& c)
{
    auto el = createEventListener(std::forward(f), std::forward(c));
    pdEngine::EventManager::getSingleton()->addListener(el);
    return el;
}
 */

}
