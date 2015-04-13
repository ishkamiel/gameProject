#ifndef PDENGINE_RESOURCEMANAGER_H_
#define PDENGINE_RESOURCEMANAGER_H_

#include "tasks/Task.h"

#include <memory>

namespace pdEngine
{

class ResourceCache;

class ResourceManager : public Task
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	void addResourceFile(const std::string& filename);

	void loadResource(const std::string& resource);
	void getResource(const std::string& resource);

protected:
	void onUpdate(TimeDelta) override;
	void onInit(void) override;
private:

	std::unique_ptr<ResourceCache> rc;
};

using ResourceManager_sptr = std::shared_ptr<ResourceManager>;
using ResourceManager_wptr = std::weak_ptr<ResourceManager>;

}
#endif
