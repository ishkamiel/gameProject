#ifndef IGRAPHICS_H_
#define IGRAPHICS_H_

namespace pdEngine
{
	class IGraphics
	{
	public:
		virtual IGraphics();
		virtual ~IGraphics();

		virtual bool v_init() { return(true); };
		virtual bool v_start() { return(true); };

	};
}

#endif
