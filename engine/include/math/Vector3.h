/* 
 * File:   Vector3.h
 * Author: ishkamiel
 *
 * Created on April 8, 2015, 3:12 PM
 */

#ifndef VECTOR3_H
#define	VECTOR3_H

#include "math/Vector3_fwd.h"
#include "Logger.h"

#include<glm/vec3.hpp>
#include<glm/geometric.hpp>
#include<iostream>

namespace pdEngine
{

float Vector3::getX(void) const noexcept
{
    return x;
}

float Vector3::getY(void) const noexcept
{
    return y;
}

float Vector3::getZ(void) const noexcept
{
    return z;
}

float Vector3::length(void) const noexcept
{
    return glm::length(static_cast<glm::vec3>(*this));
}

Vector3& Vector3::normalize(void) noexcept
{
    if ( x != 0.0f || y != 0.0f || z != 0.0f)
    {
        (*this) = glm::normalize(static_cast<glm::vec3>(*this));
        //m_Vec.reset(new glm::vec3(glm::normalize(*m_Vec)));
        // assert(glm::length(*m_Vec) > 0.999f && glm::length(*m_Vec) < 1.0001f && "vector normalization fail");
    }
    return *this;
}

inline Vector3 Vector3::getNormalized(void) const noexcept
{
    if (x == 0.0f && y == 0.0f && z == 0.0f)
        return Vector3(0.0f, 0.0f, 0.0f);

    return Vector3(glm::normalize(static_cast<glm::vec3>(*this)));
}

inline Vector3& Vector3::operator=(const Vector3& o) noexcept
{
    x  = o.x;
    y  = o.y;
    z  = o.z;
    return *this;
}

inline Vector3& Vector3::operator=(Vector3&& o) noexcept
{
    x  = o.x;
    y  = o.y;
    z  = o.z;
    return *this;
}

// inline bool operator!=(const Vector3& l, const Vector3& r) noexcept
// {
//     return !(l == r);
// }
//
// inline bool operator==(const Vector3& l, const Vector3& r) noexcept
// {
//     return (l.x == r.x && l.y == r.y && l.z == r.z); }

inline float dot (const Vector3& l, const Vector3& r) noexcept
{
    return glm::dot(static_cast<glm::vec3>(l), static_cast<glm::vec3>(r));
}

inline Vector3 operator*(const Vector3& l, const float s) noexcept
{
    return Vector3(l.x*s, l.y*s, l.z*s);
}

inline Vector3& operator*=(Vector3& l, const float s) noexcept
{
    l.x *= s;
    l.y *= s;
    l.z *= s;
    return l;
}

inline Vector3 operator*(const Vector3& l, const int s) noexcept
{
    return (l*static_cast<float>(s));
}

inline Vector3& operator*=(Vector3& l, const int s) noexcept
{
    return (l *= static_cast<float>(s));
}

}

#endif	/* VECTOR3_H */

