#include "renderer/ShaderProgram.h"

#include "exceptions/GLShaderCompileError.h"
#include "renderer/OpenglUtils.h"

#include "Logger.h"

#include <GL/glew.h> 
#include <GL/glu.h> 
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
		throw GLShaderCompileError(shader);
        //log->error("Unable to compile shader {0}, {1}", shader, getGLLog(shader));
        //throw std::runtime_error("shader compilation fail");
    }

    setID(shader);
    return true;
}

}
