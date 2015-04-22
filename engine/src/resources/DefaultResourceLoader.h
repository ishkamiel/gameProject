#pragma once

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
        virtual bool vLoadResource(char*, unsigned int, ResourceHandle*) override;
    };
}

