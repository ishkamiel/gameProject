#include "actors/ActorFactory.h"

#include "Logger.h"
#include "resources/ResourceManager.h"

#include <pugixml.hpp>

namespace pdEngine
{

ActorFactory::ActorFactory(ResourceManager_sptr rm, EventManager_sptr em)
: m_resourceManager(rm), m_eventManager(em)
{}

ActorFactory::~ActorFactory(void)
{}

Actor_sptr ActorFactory::createActor(const char* res) noexcept
{
    pugi::xml_document* xmlRoot = m_resourceManager->loadResourceXML(res);

    if (!xmlRoot)
    {
        getLogger()->error("Failed to load actor resources {}", res);
        return Actor_sptr();
    }

    Actor_sptr actor = std::make_shared<Actor>(getNextActorId());

    if (!actor->init())
    {
        getLogger()->error("Failed to initialize actor {}", res);
        return Actor_sptr();
    }

    for (auto it : *xmlRoot)
    {
        ActorComponent_sptr comp = v_createComponent(&it);
        if (!comp)
        {
            getLogger()->error("Failed to create actor subcomponent for {]", res);
            return Actor_sptr();
        }

        actor->addComponent(comp);
        comp->setOwner(actor);
    }

    actor->postInit();
    return actor;
}

ActorComponent_sptr ActorFactory::v_createComponent(const pugi::xml_node* data) noexcept
{
    std::string name(data->name());

    auto f = m_actorComponentCreators.find(name);
    if (f == m_actorComponentCreators.end()) {
        getLogger()->error("Cannot find actor component creator for {}", name);
        return ActorComponent_sptr();
    }

    return ActorComponent_sptr(f->second());
}

ActorId ActorFactory::getNextActorId(void) noexcept
{
  return m_lastActorId++;
}

}
