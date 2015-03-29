#include "resources/ResourceHandle.h"

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
        resourceCache.lock()->memoryHasBeenFreed(size);
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
}
