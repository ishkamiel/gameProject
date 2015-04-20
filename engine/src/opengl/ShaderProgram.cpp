#include "opengl/ShaderProgram.h"

#include "opengl/OpenglUtils.h"

#include "Logger.h"
#include <epoxy/gl.h>
#include <epoxy/glx.h>
#include <SDL_opengl.h>

namespace pdEngine
{

bool ShaderProgram::compileBuffer(const GLenum type, const GLchar* source)
{
    auto log = getLogger();
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint compileOk = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOk);
    if (compileOk != GL_TRUE)
    {
		throw std::runtime_error("throw GLShaderCompileError(shader);");
    }

    setID(shader);
    return true;
}

}
