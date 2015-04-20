#include "resources/ResourceManager.h"
#include "resources/ResourceCache.h"

#include <memory>

namespace pdEngine
{
    ResourceManager::ResourceManager()
    {}

    ResourceManager::~ResourceManager()
    {}

    void ResourceManager::onInit() noexcept
    {
        readyToRun();
    }

    void ResourceManager::onUpdate(int delta) noexcept
    {
        (void) delta;
    }
}
