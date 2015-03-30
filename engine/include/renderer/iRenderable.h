#ifndef IRENDERABLE_H_
#define IRENDERABLE_H_

namespace pdEngine
{
    class iRenderable
    {
    public:
        virtual void render(void) const =0;
    };
}

#endif /* IRENDERABLE_H_ */
