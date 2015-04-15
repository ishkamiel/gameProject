#ifndef PDENGINE_RESOURCEMANAGER_H_
#define PDENGINE_RESOURCEMANAGER_H_

#include "events/EventManagerImpl.h"
#include "tasks/Task.h"

namespace pdEngine
{

class ResourceManager : public Task
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	void loadResource(const std::string& resource);
	void getResource(const std::string& resource);

protected:
	void onUpdate(TimeDelta) override;
	void onInit(void) override;
private:
};

using ResourceManager_sptr = std::shared_ptr<ResourceManager>;
using ResourceManager_wptr = std::weak_ptr<ResourceManager>;

}
#endif
