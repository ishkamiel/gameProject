#ifndef PDENGINE_SHADERPROGRAM_H_
#define PDENGINE_SHADERPROGRAM_H_ 

#include <GL/glew.h>

#include <string>

namespace pdEngine
{

class ShaderProgram
{
    GLuint m_id;

public:
    virtual bool load(void) { return true; };
    virtual bool compile(void) =0;
    inline GLuint getID(void) const;
    inline void setID(GLuint id);
protected:
    bool compileBuffer(const GLenum type, const GLchar* source);
};

GLuint ShaderProgram::getID(void) const
{
    return m_id;
}

void ShaderProgram::setID(GLuint id)
{
    m_id = id;
}

}
#endif
