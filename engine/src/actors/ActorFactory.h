#pragma once

#include "actors/Actor.h"
#include "actors/ActorComponent.h"
#include <functional>
#include <map>

namespace pugi { class xml_node; }

namespace pdEngine
{
class ResourceManager;
class EventManager;
using ResourceManager_sptr = std::shared_ptr<ResourceManager>;
using EventManager_sptr = std::shared_ptr<EventManager>;

using ActorComponentCreator = std::function<ActorComponent*(void)>;

class ActorFactory
{
	using CreatorMap = std::map<std::string, ActorComponentCreator>;

	ActorId m_lastActorId;
	CreatorMap m_actorComponentCreators;
	ResourceManager_sptr m_resourceManager;
	EventManager_sptr m_eventManager;

public:
	ActorFactory(ResourceManager_sptr, EventManager_sptr);
	virtual ~ActorFactory(void);

	Actor_sptr createActor(const char* actorResource) noexcept;

protected:
	virtual ActorComponent_sptr v_createComponent(const pugi::xml_node*) noexcept;

private:
	ActorId getNextActorId(void) noexcept;
};

}

