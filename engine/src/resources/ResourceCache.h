#pragma once

#include "resources/I_ResourceContainer.h"
#include "resources/I_ResourceLoader.h"
#include "resources/Resource.h"
#include "resources/ResourceHandle.h"

#include <list>
#include <map>
#include <memory>



namespace pdEngine
{

class ResourceCache
{


protected:
    friend class ResourceHandle;

    std::list<ResourceHandle_sptr>              m_lruResources;
    std::map<std::string, ResourceHandle_sptr>  m_resources;
    std::list<ResourceLoader_sptr>              m_loaders;
    std::list<ResourceContainer_uptr>              m_containers;

    unsigned int m_cacheSize;
    unsigned int m_allocated;

public:
    ResourceCache (const unsigned int);
    virtual ~ResourceCache ();

    void addContainer(ResourceContainer_uptr);
    bool init();
    void registerLoader(ResourceLoader_sptr);

    ResourceHandle_sptr getHandle(Resource*);
    int preLoad(const std::string pattern, void (*callback)(int, bool&));
    void flush(void);

protected:
    ResourceHandle_sptr find(Resource*);
    ResourceHandle_sptr load(Resource*);

    void update(ResourceHandle_sptr);
    void free(ResourceHandle_sptr);

    bool makeRoom(unsigned int);
    char* allocate(unsigned int);
    void freeOneResource();
    void memoryHasBeenFreed(unsigned int);

private:
    ResourceHandle_sptr loadRawFile(ResourceLoader_sptr, Resource*);
    ResourceHandle_sptr loadNonRawFile(ResourceLoader_sptr, Resource*);
};

using ResourceCache_sptr = std::shared_ptr<ResourceCache>;
using ResourceCache_wptr = std::weak_ptr<ResourceCache>;
}

