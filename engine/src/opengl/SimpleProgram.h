#pragma once

#include "Logger.h"

#include <epoxy/gl.h>
#include <epoxy/glx.h>

namespace pdEngine
{

class SimpleProgram {
public:
    SimpleProgram();

    void render(void) const;
    void init(void);

private:
    //static void s_InitOpenGLProgram(void);

    GLint s_VertexPosition;
    GLint s_ModelPosition;
    GLuint m_VBO;
    GLuint m_VAO;
    GLuint m_IBO;
    GLuint m_ProgramID;

};

}
