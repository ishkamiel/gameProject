#pragma once

#include <GL/glew.h>
#include <GL/glu.h>

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
    GLint m_ProgramID;

};

}
