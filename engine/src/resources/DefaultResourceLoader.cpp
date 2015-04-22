#include "resources/DefaultResourceLoader.h"

#include <cassert>

namespace pdEngine
{
    std::regex DefaultResourceLoader::v_getRegex() const noexcept
    {
        return std::regex { ".*" };
    }

    bool DefaultResourceLoader::v_usesRawFile() const noexcept
    {
        return true;
    }

    unsigned int DefaultResourceLoader::v_getLoadedResourceSize(
        char* buffer, unsigned int size) noexcept
    {
        (void)buffer;
        return size;
    }

    bool DefaultResourceLoader::v_loadResource(
        char* buffer, unsigned int size, ResourceHandle* handle) noexcept
    {
        (void)buffer;
        (void)size;
        (void)handle;
        assert(false); // TODO implement this!
        return true;
    }
}
