#ifndef PDENGINE_EVENTLISTENER_H_
#define PDENGINE_EVENTLISTENER_H_

#include "events/I_Event.h"

#include <functional>
#include <string>

namespace pdEngine
{
    using EventListener = std::function<bool(Event_sptr)>;

    template<typename C, typename F>
    EventListener createEventListener(C&, F&);
}

namespace pdEngine
{
    // EventListener_sptr createListenerPtr(EventListener listener)
    // {
    //     return std::make_shared<EventListener>(listener);
    // }

    template<typename C, typename F>
    EventListener createEventListenerPtr(C& c, F& f)
    {
        return std::bind(f, c, std::placeholders::_1);
    }

    template<typename C, typename F>
    EventListener createEventListener(F& f, C& c)
    {
        return std::bind(f, c, std::placeholders::_1);
    }
}


#endif /* PDENGINE_EVENTLISTENER_H_ */
