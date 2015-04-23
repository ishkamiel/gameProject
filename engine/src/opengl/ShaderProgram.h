#pragma once

#include <epoxy/gl.h>
#include <epoxy/glx.h>

namespace pdEngine
{

class ShaderProgram
{
    GLuint m_id;

public:
    virtual ~ShaderProgram() {}
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
