#include "math/Plane.h"

#include "Utils.h"
#include "math/Vector3.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vector_relational.hpp>

namespace pdEngine
{

Plane::Plane (float x, float y, float z, float d)
    : n(x, y, z), d(d)
{}

Plane::Plane (const Vector3& point, const Vector3& normal)
{
    // TODO
}

Plane::Plane (const Vector3& a, const Vector3& b, const Vector3& c)
{
    // TODO
}

Plane::~Plane()
{}

Plane& Plane::operator=(const Plane& o) noexcept
{
	n = o.n;
	d = o.d;
	return *this;
}

Plane& Plane::operator=(Plane&& o) noexcept
{
	n = o.n;
	d = o.d;
	return *this;
}

}