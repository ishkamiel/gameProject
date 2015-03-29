#include "resources/ResourceCache.h"

#include "resources/DefaultResourceLoader.h"
#include "Utils.h"

#include <cassert>
#include <regex>

namespace pdEngine
{
    ResourceCache::ResourceCache (const unsigned int s, iResourceFile* f)
        : file(f), cacheSize(s*1024*1024), allocated(0)
    {}

    ResourceCache::~ResourceCache()
    {
        while (!lruResources.empty()) 
        {
            freeOneResource();
        }
    }


    bool ResourceCache::init()
    {
        bool retval = false;

        if (file->vOpen())
        {
            registerLoader(iResourceLoader_sptr(new DefaultResourceLoader()));
            retval = true;
        }
        return retval;
    }

    void ResourceCache::registerLoader(iResourceLoader_sptr l)
    {
        loaders.push_back(l);
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
        auto f = resources.find(r->getName());
        if (f == resources.end())
            return nullptr;

        return f->second;
    }

    void ResourceCache::update(ResourceHandle_sptr rh)
    {
        lruResources.remove(rh);
        lruResources.push_back(rh);
    }

    void ResourceCache::free(ResourceHandle_sptr rh)
    {
        resources.erase(rh->getResourceName());
        lruResources.remove(rh);
    }

    ResourceHandle_sptr ResourceCache::load(Resource* r)
    {
        iResourceLoader_sptr loader;
        ResourceHandle_sptr handle;

        for (auto i = loaders.begin(); i != loaders.end(); ++i)
        {
            if (std::regex_search(r->getName(), (*i)->vGetRegex()))
            {
                loader = (*i);
                break;
            }
        }

        if (!loader)
        {
            assert(loader && "DefaultResourceLoader not found");
            return nullptr;
        }

        unsigned int rawSize = file->vGetRawResourceSize(*r);
        char *rawBuffer = (loader->vUseRawFile() ?
                allocate(rawSize) : 
                new char[rawSize]);

        if (rawBuffer == nullptr) return nullptr;

        file->vGetRawResource(*r, rawBuffer);
        char* buffer = nullptr;
        unsigned int size = 0;

        if (loader->vUseRawFile())
        {
            buffer = rawBuffer;
            handle = ResourceHandle_sptr(new ResourceHandle(*r, buffer, rawSize, this));
        }
        else 
        {
            size = loader->vGetLoadedResourceSize(rawBuffer, rawSize);
            buffer = allocate(size);

            if (rawBuffer == nullptr || buffer == nullptr)
            {
                throw std::runtime_error("out of memory");
                return nullptr;
            }

            handle = ResourceHandle_sptr(
                    new ResourceHandle(*r, buffer, size, this));

            bool success = loader->vLoadResource(rawBuffer, rawSize, handle);
            safeDeleteArray(rawBuffer);

            if (!success)
                return nullptr;
        }

        lruResources.push_back(handle);
        resources[r->getName()] = handle;
        return handle;
    }


    // void memoryHasBeenFreed(unsigned int);

    char* ResourceCache::allocate(unsigned int size)
    {
        if (!makeRoom(size))
            return nullptr;

        char *mem = new char[size];

        if (mem)
            allocated += size;

        return mem;
    }

    bool ResourceCache::makeRoom(unsigned int size)
    {
        if (size > cacheSize)
            return false;

        while ((cacheSize-allocated) < size)
        {
            if (lruResources.empty())
                return false;

            freeOneResource();
        }

        return true;
    }

    void ResourceCache::freeOneResource()
    {
        ResourceHandle_sptr h = *(--(lruResources.end()));

        lruResources.pop_front();
        resources.erase(h->getResourceName());
    }

    void ResourceCache::memoryHasBeenFreed(unsigned int m)
    {
        assert((cacheSize - allocated) + m <= cacheSize && "Freeing more memory than allocated");
        allocated -= m;
    }
}
