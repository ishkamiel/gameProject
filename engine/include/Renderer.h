#ifndef PDENGINE_RENDERER_H_
#define PDENGINE_RENDERER_H_

#include "Task.h"

#include <memory>

namespace pdEngine
{
    class Renderer;
    using Renderer_sptr = std::shared_ptr<Renderer>;

    class Renderer : public Task
    {
    public:
        virtual void render() =0;
    protected:
        virtual void onInit() override =0;
        virtual void onUpdate(TimeDelta) override =0;
    };
}
#endif /* PDENGINE_RENDERER_H_ */
