#ifndef PDENGINE_EVENTBASIC_H_
#define PDENGINE_EVENTBASIC_H_

#include "events/I_Event.h"

namespace pdEngine
{
    class DefaultEvent : public I_Event
    {
        const EventTypeID typeID;
        const float timestamp;

    public:
        DefaultEvent(void) =delete;
        DefaultEvent(const EventTypeID&);
        virtual ~DefaultEvent();

        virtual inline const EventTypeID& getTypeID(void) const override;
        virtual float getTimestamp(void) const override;
    };
}

namespace pdEngine
{
    inline const EventTypeID& DefaultEvent::getTypeID(void) const 
    {
        return typeID;
    }
}

#endif /* PDENGINE_EVENTBASIC_H_ */
