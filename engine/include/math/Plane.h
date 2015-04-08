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

bool Plane::isOn(const Vector3& point) const noexcept
{
	return false;
}

bool Plane::isInside(const Vector3& point) const noexcept
{
	return false;
}

bool Plane::operator==(const Plane& o) const noexcept
{ 
    return (d == d && n == o.n);
}

bool Plane::operator!=(const Plane& o) const noexcept
{ 
	return !(*this == o);
}

}

#endif	/* PLANE_H */

