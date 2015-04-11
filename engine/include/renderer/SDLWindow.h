/* 
 * File:   SDLWindow.h
 * Author: ishkamiel
 *
 * Created on April 3, 2015, 11:09 AM
 */

#ifndef SDLWINDOW_H
#define	SDLWINDOW_H

#include "renderer/I_Window.h"

#include <SDL2/SDL.h>

namespace pdEngine
{

class SDLWindow : public I_Window
{
	
public:
	SDLWindow();
	virtual ~SDLWindow();

	virtual void init(void) override;
	virtual void openWindow(void) override;
	virtual Renderer_sptr getRenderer(void) override;
	virtual void swapFrame(void) override;

private:
	int m_WindowWidth                { 640 };
	int m_WindowHeight               { 480 };
	std::string m_WindowTitle         { "pdEngine" };

	SDL_Window* m_Window;
};

}


#endif	/* SDLWINDOW_H */

