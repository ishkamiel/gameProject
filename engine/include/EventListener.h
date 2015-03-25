#ifndef PDENGINE_EVENTLISTENER_H_
#define PDENGINE_EVENTLISTENER_H_

#include "EventManager.h"
#include "Events.h"

namespace pdEngine
{
    class EventListener;
	using EventListener_sptr =  std::unique_ptr<EventListener>;

    class EventListener
    {
        EventManager*           eventManager;
        EventID                 eventID;
        ListenerFunction_wptr   listenerFunction;

    public:
        EventID getEventID() const;
        EventName getEventName() const;
        void cancel();
        ~EventListener();

    protected:
        EventListener() =delete;
        EventListener(EventManager*, const EventID, ListenerFunction_wptr);
    };
}

#endif /* PDENGINE_EVENTLISTENER_H_ */
