#pragma once

#include "actors/ActorComponent.h"
#include "events/EventTypeID.h"

#include <memory>
#include <map>

namespace pdEngine
{
using ActorID = unsigned long;

constexpr ActorID NullActorId = 0;

class Actor
{
    friend class ActorFactory;

    using ActorComponentMap =  std::map<ActorComponentId, ActorComponent_sptr>;

private:
    ActorID m_id;
    ActorComponentMap m_components;

public:
    Actor(ActorID id);

    virtual ~Actor(void);

    bool init(/* TODO DATA */) noexcept;

    void postInit(void) noexcept;

    void destroy(void) noexcept;

    void update(int) noexcept;

    inline ActorID getID(void) const noexcept;

    template<typename T>
    inline std::weak_ptr<T> getComponent(ActorComponentId id) const noexcept;

protected:

private:
    void addComponent(ActorComponent_sptr pComponent) noexcept;
};

using Actor_sptr = std::shared_ptr<Actor>;

/*
 * Implementations
 */

inline ActorID Actor::getID(void) const noexcept
{ return m_id; }

template<typename T>
std::weak_ptr<T> Actor::getComponent(ActorComponentId id) const noexcept
{
    auto f = m_components.find(id);

    if (f != m_components.end()) {
        ActorComponent_sptr ptr{f->second};
        return std::weak_ptr<T>(
            std::static_pointer_cast<T>(ptr)
            );
    };
    return std::weak_ptr<T>();
}


}
