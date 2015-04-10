/* 
 * File:   Plane.h
 * Author: ishkamiel
 *
 * Created on April 8, 2015, 4:13 PM
 */

#ifndef PLANE_H
#define	PLANE_H

#include "math/Plane_fwd.h"
#include "math/Vector3.h"

namespace pdEngine
{

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

