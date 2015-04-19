#ifndef I_RESOURCELOADER_H_
#define I_RESOURCELOADER_H_

#include "resources/ResourceHandle.h"

#include <memory>
#include <regex>
#include <string>

namespace pdEngine
{
class I_ResourceLoader
{
public:
	virtual ~I_ResourceLoader()
	{
	}
	virtual std::regex vGetRegex() =0;
	virtual bool vUseRawFile() =0;
	virtual unsigned int vGetLoadedResourceSize(char*, unsigned int) =0;
	virtual bool vLoadResource(char*, unsigned int, ResourceHandle_sptr) =0;
};

using ResourceLoader_sptr = std::shared_ptr<I_ResourceLoader>;
}

#endif /* I_RESOURCELOADER_H_ */
