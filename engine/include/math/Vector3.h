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
	DLOG("Here we are");
	return m_Vec->x;
}

float Vector3::getY(void) const noexcept
{
	return m_Vec->y;
}

float Vector3::getZ(void) const noexcept
{
	return m_Vec->z;
}

float Vector3::length(void) const noexcept
{
    return glm::length(*m_Vec);
}

Vector3& Vector3::normalize(void) noexcept
{
    if (m_Vec->x != 0.0f ||
            m_Vec->y != 0.0f ||
            m_Vec->z != 0.0f)
    {
        m_Vec.reset(new glm::vec3(glm::normalize(*m_Vec)));
    }
    return *this;
}

inline Vector3 Vector3::getNormalized(void) const noexcept
{
    if (m_Vec->x == 0.0f &&
            m_Vec->y == 0.0f &&
            m_Vec->z == 0.0f)
    {
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    auto n = glm::normalize(*m_Vec);

    return Vector3(n);
}

inline Vector3& Vector3::operator=(const Vector3& o) noexcept
{
    m_Vec->x  = o.m_Vec->x;
    m_Vec->y  = o.m_Vec->y;
    m_Vec->z  = o.m_Vec->z;
    return *this;
}

inline Vector3& Vector3::operator=(Vector3&& o) noexcept
{
    m_Vec = std::move(o.m_Vec);
    return *this;
}

inline bool operator!=(const Vector3& lhs, const Vector3& rhs) noexcept
{
    return !(lhs==rhs);
}

inline bool operator==(const Vector3& lhs, const Vector3& rhs) noexcept
{
    return (lhs.m_Vec->x == rhs.m_Vec->x
            && lhs.m_Vec->y == rhs.m_Vec->y
            && lhs.m_Vec->z == rhs.m_Vec->z);
}

inline float dot (const Vector3& lhs, const Vector3& rhs) noexcept
{
    return glm::dot(*lhs.m_Vec, *rhs.m_Vec);
}

inline Vector3 operator*(const Vector3& lhs, const float s) noexcept
{
    return Vector3(lhs.m_Vec->x*s, lhs.m_Vec->y*s, lhs.m_Vec->z*s);
}

inline Vector3& operator*=(Vector3& lhs, const float s) noexcept
{
    (*lhs.m_Vec) *= s;
    return lhs;
}

}

#endif	/* VECTOR3_H */

