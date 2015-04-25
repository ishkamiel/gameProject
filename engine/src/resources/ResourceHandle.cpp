#include "resources/ResourceHandle.h"

#include "resources/ResourceCache.h"
#include "utils/Memory.h"

namespace pdEngine
{
    ResourceHandle::ResourceHandle(
        std::shared_ptr<Resource> r, char* b, unsigned int s)
        : m_resource(r), buffer(b), size(s)
    {}

    ResourceHandle::~ResourceHandle()
    {
        safeDeleteArray(buffer);
    }

    unsigned int ResourceHandle::getSize(void) const noexcept
    {
        return size;
    }

    const char* ResourceHandle::getBuffer(void) const noexcept
    {
        return buffer;
    }

    char* ResourceHandle::getWritableBuffer(void) noexcept
    {
        return buffer;
    }

    const std::string& ResourceHandle::getName(void) const noexcept
    {
        return m_resource->getName();
    }
}
