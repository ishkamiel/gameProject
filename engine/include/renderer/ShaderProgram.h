#ifndef PDENGINE_SHADERPROGRAM_H_
#define PDENGINE_SHADERPROGRAM_H_ 

#include <GL/glew.h>

#include <string>

namespace pdEngine
{
    GLuint loadShaderFromFile(const GLenum, const std::string);
    GLuint loadShaderFromString(const GLenum, const GLchar[]);
}

#endif
