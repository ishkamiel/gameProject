#include "resources/ResourceHandle.h"

#include "resources/ResourceCache.h"
#include "Utils.h"

namespace pdEngine
{
        //ResourceHandle(Resource&, char*, unsigned int, ResourceCache_sptr);
    ResourceHandle::ResourceHandle(Resource& r, char* b, unsigned int s, ResourceCache* rm)
        : resource(r), buffer(b), size(s), resourceCache(rm)
    {}

    ResourceHandle::~ResourceHandle()
    {
        safeDeleteArray(buffer);
        if (resourceCache != nullptr)
            resourceCache->memoryHasBeenFreed(size);
    }

    unsigned int ResourceHandle::getSize(void) const {
        return size;
    }

    char* ResourceHandle::getBuffer(void) const
    {
        return buffer;
    }

    char* ResourceHandle::getWritableBuffer(void)
    {
        return buffer;
    }

    const std::string ResourceHandle::getResourceName(void)
    {
        return resource.getName();
    }
}
