#pragma once

#include "resources/I_ResourceLoader.h"

namespace pdEngine 
{
    class DefaultResourceLoader : public I_ResourceLoader
    {

    public:
    	virtual ~DefaultResourceLoader() {}
        virtual std::regex v_getRegex() const noexcept override;
        virtual bool v_usesRawFile() const noexcept override;
        virtual unsigned int v_getLoadedResourceSize(char *, unsigned int) noexcept override;
        virtual bool v_loadResource(char *, unsigned int, ResourceHandle*) noexcept override;
    };
}

