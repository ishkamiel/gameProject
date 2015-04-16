#include "opengl/ShaderProgram.h"

#include "opengl/OpenglUtils.h"

#include "Logger.h"

#include <epoxy/gl.h>
#include <epoxy/glx.h>

namespace pdEngine
{

bool ShaderProgram::compileBuffer(const GLenum type, const GLchar* source)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compileOk = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOk);
    fatalOnShaderCompileError(compileOk);

    setID(shader);
    return true;
}

}
