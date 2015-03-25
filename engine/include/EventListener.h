#ifndef PDENGINE_EVENTLISTENER_H_
#define PDENGINE_EVENTLISTENER_H_

#include "EventData.h"

#include <string>

namespace pdEngine
{
    using EventListener = std::function<bool(EventData_sptr)>;
    using EventListener_sptr = std::shared_ptr<EventListener>;
    using EventListener_wptr = std::weak_ptr<EventListener>;

    inline EventListener_sptr createListenerPtr(EventListener);
}

namespace pdEngine
{
    EventListener_sptr createListenerPtr(EventListener listener)
    {
        return std::make_shared<EventListener>(listener);
    }
}


#endif /* PDENGINE_EVENTLISTENER_H_ */
