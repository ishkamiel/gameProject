#ifndef PDENGINE_OPENGLUTILS_H_
#define PDENGINE_OPENGLUTILS_H_ value

#include <GL/glew.h>
#include <SDL.h>

#include <string>

namespace pdEngine
{

std::string getGLLog(const GLuint);
void printGLLog(const GLuint);
bool setGLAttribute(const SDL_GLattr, const int);

}
#endif
