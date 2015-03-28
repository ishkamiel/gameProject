#ifndef PDENGINE_RENDEREROPENGL_H_
#define PDENGINE_RENDEREROPENGL_H_

#include "Renderer.h"

namespace pdEngine
{
    class RendererOpengl : public Renderer
    {
        std::string     windowTitle;

    public:
        RendererOpengl();

    public:
        RendererOpengl(std::string = "pdEngine");
        ~RendererOpengl();

        virtual void render(void) override;
        virtual void printDebugMsg(std::string) override;

    protected:

    private:
        virtual void onInit() override;
        virtual void onUpdate(TimeDelta) override;
    };
}



#endif /* PDENGINE_RENDEREROPENGL_H_ */
