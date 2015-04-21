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

pugi::xml_document* ResourceManager::loadResourceXML(const std::string& res)
{
    // TODO
    return nullptr;
}



void ResourceManager::onUpdate(int delta) noexcept
{
    (void) delta;
}
}
