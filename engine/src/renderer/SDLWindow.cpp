#include "renderer/SDLWindow.h"


#include "opengl/OpenglRenderer.h"
#include "exceptions/SDLInitFailedException.h"
#include "Logger.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <sstream>

namespace pdEngine {

SDLWindow::SDLWindow() 
: m_Window(nullptr)
{}

SDLWindow::~SDLWindow() 
{
	//if (m_Window != nullptr) delete m_Window;
}

void SDLWindow::onInit(void) noexcept
{
	initializeSDL();
	readyToRun();
}

void SDLWindow::onUpdate(int delta) noexcept
{
	static int counter = 0;
	const int limit = 1000;

	counter += delta;
	++m_updateCount;

	if (counter > limit)
	{
		static std::stringstream ss;
		ss << "pdEngine - " << m_frameCount << "fps, " << m_updateCount << "ups";
		setTitle(ss.str());
		ss.str("");
		counter = 0;
		m_updateCount = 0;
		m_frameCount = 0;
	}
}

void SDLWindow::initializeSDL(void) {
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

Renderer_sptr SDLWindow::createRenderer(void) {
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0)
			throw SDLInitFailedException("SDL_GL_SetAttribute");
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0) != 0)
			throw SDLInitFailedException("SDL_GL_SetAttribute");
	if (SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0) != 0)
			throw SDLInitFailedException("SDL_GL_SetAttribute");
	if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0)
			throw SDLInitFailedException("SDL_GL_SetAttribute");

    auto context = SDL_GL_CreateContext(m_Window);
    if (context == nullptr) 
		throw SDLInitFailedException("SDL_GL_CreateContext");

    // Enable vSync
    if (SDL_GL_SetSwapInterval(1) < 0) {
		throw SDLInitFailedException("SDL_GL_SetSwapInterval(1)");
    }

	auto renderer = std::make_shared<OpenglRenderer>();
	renderer->onInit();
	return renderer;
}

void SDLWindow::setTitle(const std::string& title) noexcept
{
	SDL_SetWindowTitle(m_Window, title.c_str());
}

void SDLWindow::swapFrame(void) 
{
    SDL_GL_SwapWindow(m_Window);
	++m_frameCount;
}

}
