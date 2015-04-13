#include "resources/ResourceManager.h"
#include "resources/ResourceCache.h"

#include <memory>

namespace pdEngine
{
    ResourceManager::ResourceManager()
    {
    	//rc = std::make_unique<ResourceCache>();
    }

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
