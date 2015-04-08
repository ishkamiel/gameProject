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


inline bool Vector3::operator==(const Vector3& o) const noexcept
{
	return ((*m_Vec)[0] == (*o.m_Vec)[0]
				&& (*m_Vec)[1] == (*o.m_Vec)[1]
				&& (*m_Vec)[2] == (*o.m_Vec)[2]);
}

inline bool Vector3::operator!=(const Vector3& o) const noexcept
{
	return !(*this == o);
}

}

#endif	/* VECTOR3_H */

