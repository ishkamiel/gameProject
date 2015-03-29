#ifndef RESOURCECACHE_H_
#define RESOURCECACHE_H_ vlue

#include "resources/iResourceFile.h"
#include "resources/iResourceLoader.h"
#include "resources/Resource.h"
#include "resources/ResourceHandle.h"

#include <list>
#include <map>
#include <memory>

namespace pdEngine
{
    class ResourceCache;
    using ResourceCache_sptr = std::shared_ptr<ResourceCache>;
    using ResourceCache_wptr = std::weak_ptr<ResourceCache>;

    using ResourceHandleList = std::list<ResourceHandle_sptr>;
    using ResourceHandleMap = std::map<std::string, ResourceHandle_sptr>;
    using ResourceLoaderList = std::list<iResourceLoader_sptr>;

    class ResourceCache
    {
    protected:
        friend class ResourceHandle;

        ResourceHandleList lruResources;
        ResourceHandleMap resources;
        ResourceLoaderList loaders;

        iResourceFile* file;

        unsigned int cacheSize;
        unsigned int allocated;
    
    public:
        /**
         * @brief 
         *
         * @param int size in Mb
         * @param iResourceFile resource file
         */
        ResourceCache (const unsigned int, iResourceFile*);
        virtual ~ResourceCache ();

        bool init();
        void registerLoader(iResourceLoader_sptr);

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
        ResourceHandle_sptr loadRawFile(iResourceLoader_sptr, Resource*);
        ResourceHandle_sptr loadNonRawFile(iResourceLoader_sptr, Resource*);
    };
}

#endif /* RESOURCECACHE_H_ */
