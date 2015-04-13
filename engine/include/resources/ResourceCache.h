#ifndef RESOURCECACHE_H_
#define RESOURCECACHE_H_ vlue

#include "resources/I_ResourceContainer.h"
#include "resources/Resource.h"
#include "resources/ResourceHandle.h"

#include <list>
#include <map>
#include <memory>

#include "I_ResourceLoader.h"


namespace pdEngine
{
    class ResourceCache;
    using ResourceCache_sptr = std::shared_ptr<ResourceCache>;
    using ResourceCache_wptr = std::weak_ptr<ResourceCache>;

    using ResourceHandleList = std::list<ResourceHandle_sptr>;
    using ResourceHandleMap = std::map<std::string, ResourceHandle_sptr>;
    using ResourceLoaderList = std::list<ResourceLoader_sptr>;

    class ResourceCache
    {
    protected:
        friend class ResourceHandle;

        ResourceHandleList lruResources;
        ResourceHandleMap resources;
        ResourceLoaderList loaders;

        I_ResourceContainer* file;

        unsigned int cacheSize;
        unsigned int allocated;
    
    public:
        /**
         * @brief 
         *
         * @param int size in Mb
         * @param iResourceFile resource file
         */
        ResourceCache (const unsigned int, I_ResourceContainer*);
        virtual ~ResourceCache ();

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
}

#endif /* RESOURCECACHE_H_ */
