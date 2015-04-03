/* 
 * File:   I_Window.h
 * Author: ishkamiel
 *
 * Created on April 3, 2015, 11:07 AM
 */

#ifndef I_WINDOW_H
#define	I_WINDOW_H

#include "renderer/I_Renderer.h"

namespace pdEngine {

class I_Window {
public:
    virtual void init(void) = 0;
    virtual void openWindow(void) =0;
	virtual Renderer_sptr getRenderer() =0;
	virtual void swapFrame(void) =0;
};

using Window_sptr = std::shared_ptr<I_Window>;
}


#endif	/* I_WINDOW_H */

