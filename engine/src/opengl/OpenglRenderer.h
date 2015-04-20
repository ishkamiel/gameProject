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

    virtual void setView(const Matrix4&) noexcept override;
    virtual void setProjection(const Matrix4&) noexcept override;
private:
    void loadShaderProgram(void) noexcept;

    Scene* m_Scene;
    //GLuint m_programID{0};

    GLuint m_programID;
    GLint m_projectUniformLocation;
    GLint m_viewUniformLocation;
    GLint m_modelUniformLocation;

    SimpleProgram m_Thing;
    //bool gRenderQuad{true};
    //GLint gVertexPos2DLocation{-1};
    //GLuint gVBO{0};
    //GLuint gIBO{0};
};

}
