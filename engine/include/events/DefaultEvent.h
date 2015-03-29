#ifndef PDENGINE_EVENTBASIC_H_
#define PDENGINE_EVENTBASIC_H_

#include "events/iEvent.h"

namespace pdEngine
{
    class DefaultEvent : public iEvent
    {
        const EventTypeID typeID;
        const EventTypeName typeName;
        const float timestamp;

    public:
        DefaultEvent(void) =delete;
        DefaultEvent(const EventTypeID&);
        virtual ~DefaultEvent();

        virtual inline const EventTypeID& getTypeID(void) const override final;
        virtual inline const EventTypeName& getTypeName(void) const override final;
        virtual float getTimestamp(void) const override;
    };
}

namespace pdEngine
{
    inline const EventTypeID& DefaultEvent::getTypeID(void) const 
    {
        return typeID;
    }

    inline const EventTypeName& DefaultEvent::getTypeName(void) const
    {
        return typeName;
    }
}

#endif /* PDENGINE_EVENTBASIC_H_ */
