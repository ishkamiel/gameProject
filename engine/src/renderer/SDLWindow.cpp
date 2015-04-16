#include "renderer/SDLWindow.h"

#include "Logger.h"
#include "renderer/OpenglRenderer.h"
#include "opengl/OpenglUtils.h"


namespace pdEngine {

SDLWindow::SDLWindow() 
: m_Window(nullptr)
{}

SDLWindow::~SDLWindow() 
{
	//if (m_Window != nullptr) delete m_Window;
}

void SDLWindow::init(void) {
    if (SDL_Init(0) != 0)
        getLogger()->fatal("SDL Init failed: {}", SDL_GetError());

    if (SDL_VideoInit(0) != 0)
        getLogger()->fatal("SDL_VideoInit failed: {}", SDL_GetError());
}

void SDLWindow::openWindow(void) {
    m_Window = SDL_CreateWindow(m_WindowTitle.c_str(),
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            m_WindowWidth, m_WindowHeight,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
}

Renderer_sptr SDLWindow::getRenderer(void) {
    auto log = getLogger();
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0)
        log->fatal("SDL_GL_setAttribute failed: {}", SDL_GetError());
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) != 0)
        log->fatal("SDL_GL_setAttribute failed: {}", SDL_GetError());
	if (SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0) != 0)
        log->fatal("SDL_GL_setAttribute failed: {}", SDL_GetError());
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0)
        log->fatal("SDL_GL_setAttribute failed: {}", SDL_GetError());

    auto context = SDL_GL_CreateContext(m_Window);
    if (context == nullptr)
        log->fatal("SDL_GL_CreateContext failed: {}", SDL_GetError());

    if (SDL_GL_SetSwapInterval(1) < 0) // Enables vSync
        log->fatal("SDL_GL_SetSwapInterval(1) failed: {}", SDL_GetError());

    fatalOnOpenGLError("OpenGL has failed before renderer creation");

	auto renderer = std::make_shared<OpenglRenderer>();
	renderer->init();
	return renderer;
}

void SDLWindow::swapFrame(void) 
{
    SDL_GL_SwapWindow(m_Window);
}

}
