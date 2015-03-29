#ifndef PDENGINE_RESOURCEMANAGER_H_
#define PDENGINE_RESOURCEMANAGER_H_

#include "EventManager.h"
#include "Task.h"

namespace pdEngine
{
    class ResourceManager;
    using ResourceManager_sptr = std::shared_ptr<ResourceManager>;
    using ResourceManager_wptr = std::weak_ptr<ResourceManager>;

    class ResourceManager : public Task
    {
        EventManager_sptr eventManager;

    public:
        ResourceManager(EventManager_sptr usigned);
        virtual ~ResourceManager();

    protected:
        void onUpdate(TimeDelta) override;
        void onInit(void) override;
    private:
    };
}

#endif
