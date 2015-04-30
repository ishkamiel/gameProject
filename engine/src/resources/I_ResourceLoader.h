#pragma once

#include <memory>
#include <regex>

namespace pdEngine
{
class ResourceHandle;

class I_ResourceLoader
{
public:
	virtual ~I_ResourceLoader()
	{ }

	virtual std::regex v_getRegex() const noexcept = 0;
	virtual bool v_usesRawFile() const noexcept = 0;
	virtual unsigned int v_getLoadedResourceSize(char *, unsigned int) noexcept = 0;
	virtual bool v_loadResource(char *, unsigned int, ResourceHandle *) noexcept = 0;
};

using ResourceLoader_sptr = std::shared_ptr<I_ResourceLoader>;
}
