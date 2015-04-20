#include "math/Vector4.h"

namespace pdEngine
{

Vector4::Vector4()
: glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)
{}

Vector4::Vector4(const float a, const float b, const float c, const float d)
: glm::vec4(a, b, c, d)
{}

Vector4::~Vector4() = default;


}
