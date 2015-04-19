#pragma once

#include "renderer/I_Renderer.h"
#include "opengl/SimpleProgram.h"
#include "renderer/Scene.h"

#include <epoxy/gl.h>
#include <epoxy/glx.h>

namespace pdEngine {

class OpenglRenderer : public I_Renderer {

public:
    OpenglRenderer();
    ~OpenglRenderer();

    virtual void onInit(void) noexcept override;
    virtual void onUpdate(const TimeDelta&) noexcept override;

    virtual void v_Render(void) noexcept override;

    virtual void printDebugMsg(const std::string&) const override;

private:
    Scene* m_Scene;
    //GLuint m_programID{0};

    SimpleProgram m_Thing;
    //bool gRenderQuad{true};
    //GLint gVertexPos2DLocation{-1};
    //GLuint gVBO{0};
    //GLuint gIBO{0};
};

}
