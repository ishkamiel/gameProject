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
	return (*m_Vec)[0];
}

float Vector3::getY(void) const noexcept
{
	return (*m_Vec)[1];
}

float Vector3::getZ(void) const noexcept
{
	return (*m_Vec)[2];
}

float Vector3::length(void) const noexcept
{
    return glm::length(*m_Vec);
}

Vector3& Vector3::normalize(void) noexcept
{
    if ((*m_Vec)[0] != 0.0f ||
            (*m_Vec)[1] != 0.0f ||
            (*m_Vec)[2] != 0.0f)
    {
        auto tmp = glm::normalize(*m_Vec);
        std::swap(*m_Vec, tmp);
    }
    return *this;
}

inline Vector3 Vector3::getNormalized(void) noexcept
{
    if ((*m_Vec)[0] == 0.0f &&
            (*m_Vec)[1] == 0.0f &&
            (*m_Vec)[2] == 0.0f)
    {
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    auto tmp = Vector3(glm::normalize(*m_Vec));
    return tmp;
}

inline Vector3& Vector3::operator=(const Vector3& o) noexcept
{
    m_Vec[0] = o.m_Vec[0];
    m_Vec[1] = o.m_Vec[1];
    m_Vec[2] = o.m_Vec[2];
    return *this;
}

inline Vector3& Vector3::operator=(Vector3&& o) noexcept
{
    m_Vec = o.m_Vec;
    o.m_Vec = nullptr;
    return *this;
}

inline bool operator!=(const Vector3& lhs, const Vector3& rhs) noexcept
{
    return !(lhs==rhs);
}

inline bool operator==(const Vector3& lhs, const Vector3& rhs) noexcept
{
    return ((*lhs.m_Vec)[0] == (*rhs.m_Vec)[0]
            && (*lhs.m_Vec)[1] == (*rhs.m_Vec)[1]
            && (*lhs.m_Vec)[2] == (*rhs.m_Vec)[2]);
}

inline float dot (const Vector3& lhs, const Vector3& rhs) noexcept
{
    return glm::dot(*lhs.m_Vec, *rhs.m_Vec);
}

inline Vector3 operator*(const Vector3& lhs, const float s) noexcept
{
    return Vector3((*lhs.m_Vec)*s);
}

inline Vector3& operator*=(Vector3& lhs, const float s) noexcept
{
    (*lhs.m_Vec) *= s;
    return lhs;
}

}
#endif	/* VECTOR3_H */

