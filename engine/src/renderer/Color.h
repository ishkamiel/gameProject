#ifndef COLOR_H_
#define COLOR_H_

#include "math/Vector4.h"

namespace pdEngine
{

class Color : private Vector4
{
public:
	Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
    virtual ~Color ();

	inline float getR(void) const noexcept { return r; }
	inline float getG(void) const noexcept { return g; }
	inline float getB(void) const noexcept { return b; }
	inline float getA(void) const noexcept { return a; }

	inline void setR(float val) noexcept { r = val; }
	inline void setG(float val) noexcept { g = val; }
	inline void setB(float val) noexcept { b = val; }
	inline void setA(float val) noexcept { a = val; }
};

}
#endif /* COLOR_H_ */
