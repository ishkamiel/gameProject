#include "resources/DefaultResourceLoader.h"
#include "resources/ResourceHandle.h"

#include "utils/Logger.h"

#include <cstring>

namespace pdEngine
{
std::regex DefaultResourceLoader::v_getRegex() const noexcept
{
	return std::regex {".*"};
}

bool DefaultResourceLoader::v_usesRawFile() const noexcept
{
	return true;
}

unsigned int DefaultResourceLoader::v_getLoadedResourceSize(
	char *buffer, unsigned int size) noexcept
{
	(void) buffer;
	return size;
}

bool DefaultResourceLoader::v_loadResource(
	char *buffer, unsigned int size, ResourceHandle *handle) noexcept
{
	PDE_ASSERT(handle->getSize() == size, "handle and buffer size missmatch");

	// TODO: handle memcpy errors, or do this some other way?
	std::memcpy(buffer, handle->getBuffer(), size);

	return true;
}

}
