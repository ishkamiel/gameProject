#include "renderer/SimpleVertexShader.h"

#include <GL/glew.h> 
#include <GL/glu.h> 
#include <SDL_opengl.h> 


namespace pdEngine {

SimpleVertexShader::SimpleVertexShader() {
}

SimpleVertexShader::~SimpleVertexShader() {
}

bool SimpleVertexShader::compile(void) {
    return compileBuffer(GL_VERTEX_SHADER,{
        "#version 140\n"
        "in vec2 LVertexPos2D;\n"
        "void main() {\n"
        "	gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );\n"
        "}"
    });
}

}
