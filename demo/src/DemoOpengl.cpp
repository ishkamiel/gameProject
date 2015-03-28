#include "DemoOpengl.h"
#include "RendererOpengl.h"
#include "RendererOpengl.h"

namespace pdEngineDemo
{
    DemoOpengl::DemoOpengl()
    {}

    DemoOpengl::~DemoOpengl()
    {}

    pdEngine::Renderer_sptr DemoOpengl::createRenderer()
    {
        return std::make_shared<pdEngine::RendererOpengl>();
    }
}
