#include "renderer/Color.h"

#include "math/Vector4.h"

namespace pdEngine 
{

Color::Color(float r, float g, float b, float a)
: Vector4(r, g, b, a)
{}

Color::~Color()
{}

}
