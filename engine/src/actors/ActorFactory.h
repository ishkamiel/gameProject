#pragma once

#include "actors/Actor.h"
#include "actors/ActorComponent.h"
#include <functional>
#include <map>

namespace pdEngine
{
using ActorComponentCreator = std::function<ActorComponent*(void)>;

class ActorFactory
{
	using CreatorMap = std::map<std::string, ActorComponentCreator>;

	ActorId m_lastActorId;
	CreatorMap m_actorComponentCreators;

public:
	ActorFactory(void);
	virtual ~ActorFactory(void);

	Actor_sptr createActor(const char* actorResource) noexcept;

protected:
	virtual ActorComponent_sptr v_createComponent(/* TODO DATA */) noexcept;

private:
	ActorId getNextActorId(void) noexcept;
};

}

