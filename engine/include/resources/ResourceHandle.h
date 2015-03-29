#ifndef PDENGINE_RESOURCEHANDLE_H_
#define PDENGINE_RESOURCEHANDLE_H_ value

#include "resources/ResourceCache.h"
#include "resources/Resource.h"

#include <memory>

namespace pdEngine
{
    class ResourceHandle;
    using ResourceHandle_sptr = std::shared_ptr<ResourceHandle>;

    class ResourceHandle
    {
        friend class ResourceCache;

        Resource resource;
        char *buffer;
        unsigned int size;
        // iResourceExtraData_sptr extra;
        ResourceCache* resourceCache;

    public:
        //ResourceHandle(Resource&, char*, unsigned int, ResourceCache*);
        ResourceHandle(Resource*, char*, unsigned int, ResourceCache*);
        //ResourceHandle( char*, unsigned int, ResourceCache*);
        virtual ~ResourceHandle();

        unsigned int getSize(void) const;
        char* getBuffer(void) const;
        char* getWritableBuffer(void);
        // iResourceExtraData_sptr getExtra();
        // void setExtra(iResourceExtraData_sptr);

    protected:
    private:
    };
}

#endif
