#include "resources/ResourceManager.h"

namespace pdEngine
{
    ResourceManager::ResourceManager(EventManager_sptr em)
        : eventManager(em)
    {}

    ResourceManager::~ResourceManager()
    {}

    void ResourceManager::onInit()
    {
    }

    void ResourceManager::onUpdate(TimeDelta delta)
    {
        (void) delta;
    }
}
