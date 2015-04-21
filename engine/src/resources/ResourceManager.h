#pragma once

#include "tasks/Task.h"

#include <memory>

namespace pugi { class xml_document; }

namespace pdEngine
{

class ResourceCache;

class ResourceManager : public Task
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	std::string v_getTaskName(void) const noexcept override { return "Resource Manager"; }

	void addResourceFile(const std::string& filename);

	pugi::xml_document* loadResourceXML(const std::string& resource);

	void loadResource(const std::string& resource);
	void getResource(const std::string& resource);

protected:
	void onUpdate(int deltaMs) noexcept override;
	void onInit(void) noexcept override;
private:

	std::unique_ptr<ResourceCache> rc;
};

using ResourceManager_sptr = std::shared_ptr<ResourceManager>;
using ResourceManager_wptr = std::weak_ptr<ResourceManager>;

}
