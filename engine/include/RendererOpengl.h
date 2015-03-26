#ifndef PDENGINE_RENDEREROPENGL_H_
#define PDENGINE_RENDEREROPENGL_H_

#include "Renderer.h"

namespace pdEngine
{
    class RendererOpengl : public Renderer
    {
    public:
        RendererOpengl();

        virtual void onInit() override;
        virtual void onUpdate(TimeDelta) override;
    private:
    };
}



#endif /* PDENGINE_RENDEREROPENGL_H_ */
