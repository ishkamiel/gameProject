#pragma once

#include "Logger.h"
#include "renderer/I_Window.h"

#include <SDL2/SDL.h>

namespace pdEngine
{

class SDLWindow : public I_Window, public Task
{
	
public:
	SDLWindow();
	virtual ~SDLWindow();

	virtual std::string v_getTaskName() const noexcept override { return "SDL Window"; }

	virtual void onInit(void) noexcept override;
	virtual void onUpdate(int) noexcept override;

	virtual void openWindow(void) override;
	virtual Renderer_sptr createRenderer(void) override;
	virtual void swapFrame(void) override;

	virtual void setTitle(const std::string&) noexcept override;

private:
	void initializeSDL(void);

	int m_WindowWidth                { 640 };
	int m_WindowHeight               { 480 };
	std::string m_WindowTitle         { "pdEngine" };

	SDL_Window* m_Window;

	int m_updateCount { 0 };
	int m_frameCount { 0 };
};

}
