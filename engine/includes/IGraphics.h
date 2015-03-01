#ifndef IGRAPHICS_H_
#define IGRAPHICS_H_

#include <memory>

namespace pdEngine
{
    class IGraphics;

    typedef std::shared_ptr<IGraphics> Graphics_sptr;

	class IGraphics
	{
	public:
		IGraphics() {};
		virtual ~IGraphics() =0;

		virtual bool init() =0;
		virtual bool start() =0;
		virtual bool shutdown() =0;
	};
}

#endif
