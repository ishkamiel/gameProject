#ifndef IRESOURCEFILE_H_
#define IRESOURCEFILE_H_ value

#include "resources/Resource.h"

namespace pdEngine
{
    class iResourceFile
    {
    public:
        virtual bool vOpen(void) =0;
        virtual int vGetRawResourceSize(const Resource &r) =0;
        virtual int vGetRawResource(const Resource &r, char *buffer)= 0;
        virtual int vGetNumResources(void) const =0;
        virtual std::string vGetResourceName(int num) const =0;
    };
}

#endif /* IRESOURCEFILE_H_ */   
