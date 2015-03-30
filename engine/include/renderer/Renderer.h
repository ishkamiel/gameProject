#ifndef PDENGINE_RENDERER_H_
#define PDENGINE_RENDERER_H_

#include "renderer/iRenderable.h"
#include "Task.h"

#include <memory>
#include <string>

namespace pdEngine
{
    class Renderer;
    using Renderer_sptr = std::shared_ptr<Renderer>;

    class Renderer : public Task, public iRenderable
    {
    public:
        virtual void render(void) const override =0;
        virtual void printDebugMsg(std::string) =0;
    protected:
        virtual void onInit() override =0;
        virtual void onUpdate(TimeDelta) override =0;
    };
}
#endif /* PDENGINE_RENDERER_H_ */
