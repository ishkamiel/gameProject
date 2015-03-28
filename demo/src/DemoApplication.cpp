#include "DemoApplication.h"
#include "RendererOpengl.h"
#include "RendererSDL.h"

namespace pdEngineDemo
{
    DemoApplication::DemoApplication()
    {}

    DemoApplication::~DemoApplication()
    {}

    pdEngine::Renderer_sptr DemoApplication::createRenderer()
    {
        return std::make_shared<pdEngine::RendererSDL>();
    }
}
