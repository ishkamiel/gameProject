#include "renderer/OpenglUtils.h"

#include "Logger.h"
#include "renderer/OpenglUtils.h"

#include <GL/glew.h> 
#include <GL/glu.h> 
#include <SDL_opengl.h> 

namespace pdEngine
{
    GLuint loadShaderFromFile(const GLenum type, const std::string filename)
    {
        (void)type;
        (void)filename;
        throw std::logic_error("not implemented");
        return 0;
    }

    GLuint loadShaderFromString(const GLenum type, const GLchar source[])
    {
        auto log = GET_LOGGER();
        GLuint shader = glCreateShader(type);

        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint compileOk = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOk);
        if (compileOk != GL_TRUE)
        {
            log->error("Unable to compile shader {0}", shader);
            printGLLog(shader);
            throw std::runtime_error("shader compilation fail");
        }

        return shader;
    }
}

