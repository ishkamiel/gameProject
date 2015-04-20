#include "ActorFactory.h"

namespace pdEngine
{

ActorFactory::ActorFactory(void)
{}

ActorFactory::~ActorFactory(void)
{}

Actor_sptr ActorFactory::createActor(const char* actorResource) noexcept
{
    /*
    // Grab the root XML node
    TiXmlElement* pRoot =
        XmlResourceLoader::LoadAndReturnRootXmlElement(actorResource);
    if (!pRoot)
    {
        GCC_ERROR(“Failed to create actor from resource: ” + std::string(actorResource));
        return StrongActorPtr();
    }

    // create the actor instance
    StrongActorPtr pActor(GCC_NEW Actor(GetNextActorId()));
    if (!pActor->Init(pRoot))
    {
        GCC_ERROR(“Failed to initialize actor: ” + std::string(actorResource));
        return StrongActorPtr();
    }

    // Loop through each child element and load the component
    for (TiXmlElement* pNode = pRoot->FirstChildElement(); pNode;
        pNode = pNode->NextSiblingElement())
    {
        StrongActorComponentPtr pComponent(CreateComponent(pNode));
        if (pComponent)
        {
            pActor->AddComponent(pComponent);
            pComponent->SetOwner(pActor);
        }
        else
        {
            return StrongActorPtr();
        }
    }

    // Now that the actor has been fully created, run the post init phase
    pActor->PostInit();

    return pActor;
   */
    return std::shared_ptr<Actor>();
}

ActorComponent_sptr ActorFactory::v_createComponent(/* TODO DATA */) noexcept
{
    return std::shared_ptr<ActorComponent>();
}

ActorId ActorFactory::getNextActorId(void) noexcept
{
  return m_lastActorId++;
}

}
