#include "resources/ResourceHandle.h";

namespace pdEngine
{
    ResourceHandle::ResourceHandle(Resource& r,
                char *b,
                unsigned int s,
                ResourceManager_sptr rm)
        : resource(r), buffer(b), size(s), resourceManager(rm)
    {}

    ResourceHandle::~ResourceHandle()
    {

    }

        unsigned int getSize(void) const;
        char* getBuffer(void) const;
        char* getWritableBuffer(void);

    protected:
    private:
}
