#include "math/Plane.h"

#include "utils/Logger.h"

namespace pdEngine
{

Plane::Plane() = default;
Plane::Plane(const Plane& plane) = default;
Plane::Plane(Plane&&) = default;

Plane::Plane (float x, float y, float z, float d)
    : n(x, y, z), d(d)
{
    assert(n.length() != 0.0f && "zero length normal :(");
    n.normalize();
    assert(isValid());
}

Plane::Plane (const Vector3& point, const Vector3& normal)
: n(normal.getNormalized()), d(dot(n, point))
{
    assert(normal.length() != 0.0f && "zero length normal :(");
    assert(isValid());
}

Plane::Plane (const Vector3& a, const Vector3& b, const Vector3& c)
{
    n = cross(a - c, b - c);
    assert(n.length() != 0.0f && "zero length normal :(");

    n.normalize();
    d = dot(n, a);
    assert(isValid());
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

bool Plane::isValid(void) const noexcept
{
    auto normalLength = n.length();

    if (std::abs(normalLength - 1.0f) > 0.00001f) {
        PDE_ERROR << "We have an invalid Plane, normal length is: " << n.length();
        // TODO: Vector3 lenght screwed....
        // return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Plane& plane) noexcept
{
    return (os << "{" << plane.n << ", " << plane.d << "}");
}


}
