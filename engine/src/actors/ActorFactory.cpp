#include "actors/ActorFactory.h"

#include "utils/Logger.h"
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
    auto xmlRoot = ResourceManager::get()->loadXML(res);

    if (!xmlRoot)
    {
        PDE_ERROR  << "Failed to load actor resources " <<  res;
        return Actor_sptr();
    }

    Actor_sptr actor = std::make_shared<Actor>(getNextActorId());

    if (!actor->init())
    {
        PDE_ERROR << "Failed to initialize actor "  << res;
        return Actor_sptr();
    }

    for (auto it : *xmlRoot)
    {
        ActorComponent_sptr comp = v_createComponent(&it);
        if (!comp)
        {
            PDE_ERROR << "Failed to create actor subcomponent for " << res;
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
        PDE_ERROR << "Cannot find actor component creator for " << name;
        return ActorComponent_sptr();
    }

    return ActorComponent_sptr(f->second());
}

ActorId ActorFactory::getNextActorId(void) noexcept
{
  return m_lastActorId++;
}

}
