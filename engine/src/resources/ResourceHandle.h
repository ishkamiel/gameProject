#pragma once

#include "resources/Resource.h"

#include <memory>

namespace pdEngine
{

class ResourceHandle
{
    Resource resource;
    char *buffer;
    unsigned int size;
    // iResourceExtraData_sptr extra;

public:
    ResourceHandle(Resource&, char*, unsigned int);
    virtual ~ResourceHandle();

    unsigned int getSize(void) const;
    char* getBuffer(void) const;
    char* getWritableBuffer(void);
    const std::string getResourceName();

    // iResourceExtraData_sptr getExtra();
    // void setExtra(iResourceExtraData_sptr);

protected:
private:

};

using ResourceHandle_sptr = std::shared_ptr<ResourceHandle>;
}
