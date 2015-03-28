#include "DemoSDL.h"
#include "RendererOpengl.h"
#include "RendererSDL.h"

namespace pdEngineDemo
{
    DemoSDL::DemoSDL()
    {}

    DemoSDL::~DemoSDL()
    {}

    pdEngine::Renderer_sptr DemoSDL::createRenderer()
    {
        return std::make_shared<pdEngine::RendererSDL>();
    }
}
