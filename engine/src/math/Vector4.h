#pragma once

#include "math/Math_fwd.h"

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>

namespace pdEngine
{

class Vector4 : public glm::vec4
{
public:
	Vector4();
	Vector4(const float, const float, const float, const float);
	virtual ~Vector4();
};

}
