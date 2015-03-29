#include "resources/DefaultResourceLoader.h"

namespace pdEngine
{
    std::regex DefaultResourceLoader::vGetRegex()
    {
        std::regex re { ".*" };
        return re;
    }

    bool DefaultResourceLoader::vUseRawFile()
    {
        return true;
    }

    unsigned int DefaultResourceLoader::vGetLoadedResourceSize(char* b, unsigned int s)
    {
        (void)b;
        return s;
    }

    bool DefaultResourceLoader::vLoadResource(char*, unsigned int, ResourceHandle_sptr)
    {
        return true;
    }
}
