#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

#include <memory>   

namespace pdEngine
{

class I_Renderable;
using Renderable_sptr = std::shared_ptr<I_Renderable>;

class I_Renderable
{
public:
	virtual void render(void) const =0;
};
}

#endif /* IRENDERABLE_H_ */
