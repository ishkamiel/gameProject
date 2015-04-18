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
    }

    void ResourceManager::onUpdate(const TimeDelta& delta) noexcept
    {
        (void) delta;
    }
}
