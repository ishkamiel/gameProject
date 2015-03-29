#ifndef IRESOURCELOADER_H_
#define IRESOURCELOADER_H_

#include "resources/ResourceHandle.h"

#include <memory>
#include <regex>
#include <string>

namespace pdEngine
{
    class iResourceLoader;
    using iResourceLoader_sptr = std::shared_ptr<iResourceLoader>;

    class iResourceLoader
    {
    public:
        virtual std::regex vGetRegex() =0;
        virtual bool vUseRawFile() =0;
        virtual unsigned int vGetLoadedResourceSize(char*, unsigned int) =0;
        virtual bool vLoadResource(char*, unsigned int, ResourceHandle_sptr) =0;
    };
}

#endif /* IRESOURCELOADER_H_ */
