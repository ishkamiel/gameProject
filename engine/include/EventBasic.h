#ifndef PDENGINE_EVENTBASIC_H_
#define PDENGINE_EVENTBASIC_H_

#include "Event.h"

namespace pdEngine
{
    class EventBasic : public Event
    {
        const EventTypeID typeID;
        const EventTypeName typeName;
        const float timestamp;

    public:
        EventBasic(void) =delete;
        EventBasic(const EventTypeID&);
        virtual ~EventBasic();

        virtual inline const EventTypeID& getTypeID(void) const override final;
        virtual inline const EventTypeName& getTypeName(void) const override final;
        virtual float getTimestamp(void) const override;
    };
}

namespace pdEngine
{
    inline const EventTypeID& EventBasic::getTypeID(void) const 
    {
        return typeID;
    }

    inline const EventTypeName& EventBasic::getTypeName(void) const
    {
        return typeName;
    }
}

#endif /* PDENGINE_EVENTBASIC_H_ */
