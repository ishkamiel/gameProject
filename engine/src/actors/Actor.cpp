#include "actors/Actor.h"

namespace pdEngine
{

Actor::Actor(ActorID id)
: m_id(id)
{

}

Actor::~Actor(void)
{ }

bool Actor::init() noexcept
{
	return true;
}

void Actor::postInit(void) noexcept
{

}

void Actor::destroy(void) noexcept
{

}

void Actor::update(int deltaMs) noexcept
{

}

void Actor::addComponent(ActorComponent_sptr pComponent) noexcept
{

}

}