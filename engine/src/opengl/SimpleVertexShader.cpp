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
        "#version 330\n"
        "uniform mat4 View, Project;\n"
        "in vec4 Vertex;\n"
        "in mat4 Model;\n"
        "void main() {\n"
        "	gl_Position = View * Model * Project * Vertex;\n"
        "}"
    });
}

}
