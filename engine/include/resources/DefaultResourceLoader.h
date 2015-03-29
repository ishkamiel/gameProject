#include "resources/iResourceLoader.h"

namespace pdEngine 
{
    class DefaultResourceLoader : public iResourceLoader
    {
    public:
        virtual std::regex vGetRegex() override;
        virtual bool vUseRawFile() override;
        virtual unsigned int vGetLoadedResourceSize(char*, unsigned int) override;
        virtual bool vLoadResource(char*, unsigned int, ResourceHandle_sptr) override;
    };
}
