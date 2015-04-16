#ifndef PLANE_H
#define	PLANE_H

#include "math/Plane.h"
#include "math/Vector3.h"

#include <ostream>

namespace pdEngine
{

class Plane
{
	friend inline bool operator==(const Plane& lhs, const Plane& rhs) noexcept;
	friend inline bool operator!=(const Plane& lhs, const Plane& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Plane& plane) noexcept;

public:
	Plane();
    Plane(const Plane&);
	Plane(Plane&&);
    Plane(float x, float y, float z, float d);
    Plane(const Vector3& point, const Vector3& normal);
    Plane(const Vector3& a, const Vector3& b, const Vector3& c);
    virtual ~Plane();

	Plane& operator=(const Plane&) noexcept;
	Plane& operator=(Plane&&) noexcept;

    inline const Vector3& getNormal(void) const noexcept;
    inline float getDistance(void) const noexcept;

    inline float distanceTo(const Vector3& point) const noexcept;
    inline bool isOn(const Vector3& point) const noexcept;
    inline bool isInside(const Vector3& point) const noexcept;

    bool isValid(void) const noexcept;

private:
	Vector3 n;
	float d;
};

auto Plane::getNormal(void) const noexcept -> const Vector3&
{
    return n;
}

float Plane::getDistance(void) const noexcept
{
    return d;
}

float Plane::distanceTo(const Vector3& point) const noexcept
{
    return dot(n, point) - d;
}

bool Plane::isOn(const Vector3& point) const noexcept
{
    return (distanceTo(point) == 0.0f);
}

bool Plane::isInside(const Vector3& point) const noexcept
{
    return (distanceTo(point) <= 0);
}

inline bool operator==(const Plane& lhs, const Plane& rhs) noexcept
{
    return (lhs.d == rhs.d && lhs.n == rhs.n);
}

inline bool operator!=(const Plane& lhs, const Plane& rhs) noexcept
{
    return !(lhs == rhs);
}

}

#endif	/* PLANE_H */

