#include "renderer/SDLWindow.h"

#include "renderer/OpenglRenderer.h"
#include "exceptions/SDLInitFailedException.h"
#include "exceptions/GLEWInitFailedException.h"
#include "Logger.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace pdEngine {

SDLWindow::SDLWindow() 
: m_Window(nullptr)
{}

SDLWindow::~SDLWindow() 
{
	//if (m_Window != nullptr) delete m_Window;
}

void SDLWindow::init(void) {
    if (SDL_Init(0) != 0) {
		throw SDLInitFailedException("SDL_Init");
    }

    if (SDL_VideoInit(0) != 0) {
        throw SDLInitFailedException("SDL_VideInit");
    }
}

void SDLWindow::openWindow(void) {
    m_Window = SDL_CreateWindow(m_WindowTitle.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            m_WindowWidth, m_WindowHeight,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
}

Renderer_sptr SDLWindow::getRenderer(void) {
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) != 0) 
			throw SDLInitFailedException("SDL_GL_SetAttribute");
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1) != 0)
			throw SDLInitFailedException("SDL_GL_SetAttribute");
	if (SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4) != 0)
			throw SDLInitFailedException("SDL_GL_SetAttribute");
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0)
			throw SDLInitFailedException("SDL_GL_SetAttribute");

    auto context = SDL_GL_CreateContext(m_Window);
    if (context == nullptr) 
		throw SDLInitFailedException("SDL_GL_CreateContext");

    // initialize GLEW
    glewExperimental = GL_TRUE;

    GLenum glewError = glewInit();
    if (glewError != 0) {
		throw GLEWInitFailedException(glewError);
    }

    // Enable vSync
    if (SDL_GL_SetSwapInterval(1) < 0) {
		throw SDLInitFailedException("SDL_GL_SetSwapInterval(1)");
    }

	auto renderer = std::make_shared<OpenglRenderer>();
	renderer->init();
	return renderer;
}

void SDLWindow::swapFrame(void) 
{
    SDL_GL_SwapWindow(m_Window);
}

}
