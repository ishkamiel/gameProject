#pragma once

#include "actors/Actor.h"

class ActorComponent
{
    friend class ActorFactory;

    class XMLData;

public:
    virtual ~ActorComponent(void)
    { };

    virtual bool v_init(XMLData *data) = 0;

    virtual void v_postInit(void) noexcept
    { };

    virtual void v_onUpdate(int deltaMS) noexcept
    { };

protected:
    virtual ComponentId v_getComponentId(void) const noexcept = 0;
    inline void setOwner(Actor_sptr owner) const noexcept { m_owner = owner; }
    inline Actor_sptr getOwner(void) const noexcept { return m_owner; }

private:
    Actor_sptr m_owner;
};

};



