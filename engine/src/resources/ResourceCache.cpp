#include "resources/ResourceCache.h"
#include "resources/DefaultResourceLoader.h"
#include "Logger.h"
#include "Utils.h"

#include <cassert>
#include <regex>

namespace pdEngine
{
ResourceCache::ResourceCache (const unsigned int s)
    : m_cacheSize(s*1024*1024), m_allocated(0)
{}

ResourceCache::~ResourceCache()
{
    while (!m_lruResources.empty())
    {
        freeOneResource();
    }
}

void ResourceCache::addContainer(ResourceContainer_sptr container)
{
    m_containers.push_back(container);
}


bool ResourceCache::init()
{
    bool retval = true;

    for (auto container : m_containers)
    {
        if (container->vOpen()) {
            registerLoader(ResourceLoader_sptr(new DefaultResourceLoader()));
        }
        else
        {
            getLogger()->warn("Unable to open container {}", container->v_getName());
            retval = false;
        }

    }

    return retval;
}

void ResourceCache::registerLoader(ResourceLoader_sptr l)
{
    m_loaders.push_back(l);
}

ResourceHandle_sptr ResourceCache::getHandle(Resource* r)
{
    ResourceHandle_sptr handle { find(r) };

    if (!handle)
        handle = load(r);
    else
        update(handle);

    return handle;
}

int ResourceCache::preLoad(const std::string p, void (*callback)(int, bool&))
{
    (void)p;
    (void)callback;
    throw std::runtime_error("preLoad not implemented");
}

void ResourceCache::flush(void)
{
}

ResourceHandle_sptr ResourceCache::find(Resource* r)
{
    auto f = m_resources.find(r->getName());
    if (f == m_resources.end())
        return nullptr;

    return f->second;
}

void ResourceCache::update(ResourceHandle_sptr rh)
{
    m_lruResources.remove(rh);
    m_lruResources.push_back(rh);
}

void ResourceCache::free(ResourceHandle_sptr rh)
{
    // ResourceHande shared_ptr destruction triggers acctuall release of memory.
    // This simply removes the cache reference to the shared_ptr.
    m_resources.erase(rh->getResourceName());

    m_lruResources.remove(rh);
}


ResourceHandle_sptr ResourceCache::load(Resource* r)
{
    auto container = getContainer(r);
    if (!container) {
        getLogger()->warn("Unable to find ResourceContianer for {}", r->getName());
        return ResourceHandle_sptr();
    }
    auto loader = getLoader(r);
    if (!loader) {
        getLogger()->warn("Unable to find ResourceLoader for {]", r->getName());
        return ResourceHandle_sptr();
    }

    ResourceHandle *rawPointer;

    if (loader->vUseRawFile()) {
        rawPointer = loadRaw(container, loader, r);
    }
    else {
        rawPointer = loadNonRaw(container, loader, r);
    }

    auto handle = std::shared_ptr<ResourceHandle>(
        rawPointer,
        [=](ResourceHandle *p) {
            /* This makes sure the cache is notified without needing to
             * involve ResourceHandle internals */
            memoryHasBeenFreed(p->getSize());
            delete p;
        });

    m_lruResources.push_back(handle);
    m_resources[r->getName()] = handle;
    return handle;
}


char* ResourceCache::allocate(unsigned int size)
{
    if (!makeRoom(size))
        return nullptr;

    char* mem;

    try {
        mem = new char[size];
    }
    catch (const std::bad_alloc& e) {
        getLogger()->error("out of memory: ", e.what());
        assert(false);
        return nullptr;
    }

    if (mem != nullptr)
        m_allocated += size;

    return mem;
}

bool ResourceCache::makeRoom(unsigned int size)
{
    if (size > m_cacheSize)
        return false;

    while ((m_cacheSize-m_allocated) < size)
    {
        if (m_lruResources.empty())
            return false;

        freeOneResource();
    }

    return true;
}

void ResourceCache::freeOneResource()
{
    ResourceHandle_sptr h = *(--(m_lruResources.end()));

    m_lruResources.pop_front();
    m_resources.erase(h->getResourceName());
}

void ResourceCache::memoryHasBeenFreed(unsigned int m)
{
    assert(m_allocated > m); // Freeing more memory than allocated
    m_allocated -= m;
}

ResourceContainer_sptr ResourceCache::getContainer(Resource* r) noexcept
{
    // TODO implement this!!!!
    return ResourceContainer_sptr();
}

ResourceLoader_sptr ResourceCache::getLoader(Resource* r) noexcept
{
    for (auto l : m_loaders) {
        if (std::regex_search(r->getName(), l->vGetRegex())) {
            return l;
        }
    }
    return ResourceLoader_sptr();
}

ResourceHandle* ResourceCache::loadRaw(
    ResourceContainer_sptr file, ResourceLoader_sptr loader, Resource* r)
{
    unsigned int rawSize = file->vGetRawResourceSize(*r);
    char *rawBuffer = allocate(rawSize);

    if (rawBuffer == nullptr) {
        getLogger()->fatal("out of memory");
    }

    file->vGetRawResource(*r, rawBuffer);
    return new ResourceHandle(*r, rawBuffer, rawSize);
}

ResourceHandle* ResourceCache::loadNonRaw(
    ResourceContainer_sptr file, ResourceLoader_sptr loader, Resource* r)
{
    unsigned int rawSize = file->vGetRawResourceSize(*r);

    // this is going to be just a temporary buffer.
    auto rawBuffer = new char[rawSize];

    if (rawBuffer == nullptr) {
        getLogger()->fatal("out of memory");
    }

    file->vGetRawResource(*r, rawBuffer);

    auto size = loader->vGetLoadedResourceSize(rawBuffer, rawSize);
    char* buffer = allocate(size);

    if (buffer == nullptr) {
        getLogger()->fatal("out of memory");
    }

    auto handle = new ResourceHandle(*r, buffer, size);

    bool success = loader->vLoadResource(rawBuffer, rawSize, handle);
    safeDeleteArray(rawBuffer);

    if (!success) return nullptr;
    return handle;
}

}
