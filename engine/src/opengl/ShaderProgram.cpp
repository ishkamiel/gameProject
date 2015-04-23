#include "opengl/ShaderProgram.h"

#include "opengl/OpenglUtils.h"
#include "utils/Logger.h"

#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <SDL_opengl.h>

namespace pdEngine
{

bool ShaderProgram::compileBuffer(const GLenum type, const GLchar* source)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compileOk = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOk);
    if (compileOk != GL_TRUE)
    {
        PDE_FATAL << "Error compiling shader " << getGLInfoLog(shader);
        exit(EXIT_FAILURE);
    }

    setID(shader);
    return true;
}

}
