#pragma once

#include <GL/glew.h>
#include <GL/glu.h>

namespace pdEngine {

class SimpleProgram {
public:
    SimpleProgram();
    void render(void);
    void init(void);

private:
    static void s_InitOpenGLProgram(void);

    static GLuint s_VBO{0};
    static GLuint s_IBO{0};
    static bool s_InitDone { false };
    static GLint s_ProgramID { -1 };
};

}
