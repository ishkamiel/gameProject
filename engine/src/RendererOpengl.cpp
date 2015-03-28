#include "RendererOpengl.h"

#include <GL/glew.h> 
#include <GL/glu.h> 
#include <SDL.h> 
#include <SDL_opengl.h> 
// #include <stdio.h> 
// #include <string>

namespace pdEngine 
{
    RendererOpengl::RendererOpengl(std::string windowTitle)
        : windowTitle(windowTitle)
    {}

    RendererOpengl::~RendererOpengl()
    {}

    void RendererOpengl::onInit(void)
    {}

    void RendererOpengl::onUpdate(TimeDelta delta)
    {
        (void)delta;
    }

    void RendererOpengl::render()
    {
    }

    void RendererOpengl::printDebugMsg(std::string msg)
    {
        (void)msg;
    }
}
