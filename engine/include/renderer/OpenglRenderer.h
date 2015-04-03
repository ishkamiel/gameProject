#ifndef PDENGINE_RENDEREROPENGL_H_
#define PDENGINE_RENDEREROPENGL_H_

#include "renderer/I_Renderer.h"

#include <GL/glew.h> 
#include <GL/glu.h> 

namespace pdEngine {

class OpenglRenderer : public I_Renderer {

public:
    OpenglRenderer();
    ~OpenglRenderer();

    virtual void render(void) const override;
    virtual void printDebugMsg(const std::string&) const override;
    virtual void init() override;

private:
    GLuint m_programID{0};

    bool gRenderQuad{true};
    GLint gVertexPos2DLocation{-1};
    GLuint gVBO{0};
    GLuint gIBO{0};
};

}
#endif /* PDENGINE_RENDEREROPENGL_H_ */
