#pragma once

#include "events/EventTypeID.h"
#include "events/DefaultEvent.h"

#include <memory>

namespace pdEngine
{

class ActorCreatedEvent : public DefaultEvent
{
	std::weak_ptr<Actor> m_actor_wptr;

public:
	static constexpr EventTypeID typeID(void)
	{ return getEventID("ActorCreated"); }

	ActorCreatedEvent(std::shared_ptr<Actor> actor_sptr)
	: DefaultEvent(typeID()), m_actor_wptr(actor_sptr)
	{}

	std::weak_ptr<Actor> getActor(void) const noexcept
	{  return m_actor_wptr; }
};

}
