#ifndef I_DEFAULTRESOURCELOADER_H_
#define I_DEFAULTRESOURCELOADER_H_

#include "resources/I_ResourceLoader.h"

namespace pdEngine 
{
    class DefaultResourceLoader : public I_ResourceLoader
    {
    public:
    	virtual ~DefaultResourceLoader() {}
        virtual std::regex vGetRegex() override;
        virtual bool vUseRawFile() override;
        virtual unsigned int vGetLoadedResourceSize(char*, unsigned int) override;
        virtual bool vLoadResource(char*, unsigned int, ResourceHandle_sptr) override;
    };
}

#endif /* I_DEFAULTRESOURCELOADER_H_ */
