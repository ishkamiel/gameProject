#pragma once

#include <memory>

namespace pugi { class xml_node; }

namespace pdEngine
{
class Actor;
using Actor_sptr = std::shared_ptr<Actor>;

using ActorComponentId = unsigned int;

class ActorComponent
{
    friend class ActorFactory;

	Actor_sptr m_owner;

public:
    virtual ~ActorComponent(void)
    { };

    virtual bool v_init(const pugi::xml_node *data) noexcept = 0;

    virtual void v_postInit(void) noexcept
    { };

    virtual void v_onUpdate(int deltaMS) noexcept
    { };

protected:
    virtual ActorComponentId v_getComponentId(void) const noexcept = 0;
    inline void setOwner(Actor_sptr owner) noexcept { m_owner = owner; }
    inline Actor_sptr getOwner(void) const noexcept { return m_owner; }

};

using ActorComponent_sptr = std::shared_ptr<ActorComponent>;

}
