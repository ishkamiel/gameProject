#include "math/Vector3.h"

#include "Utils.h"

#include <glm/vec3.hpp>

namespace pdEngine
{

Vector3::Vector3(void)
: m_Vec(new glm::vec3())
{}

Vector3::Vector3(const float x, const float y, const float z)
: m_Vec(new glm::vec3(x,y,z))
{}

Vector3::Vector3(const Vector3& vec)
: m_Vec(new glm::vec3( (*(vec.m_Vec))[0], (*(vec.m_Vec))[1], (*(vec.m_Vec))[2]))
{}

Vector3::Vector3(Vector3&& vec)
: m_Vec(vec.m_Vec)
{
	vec.m_Vec = nullptr;
}
 
 Vector3::~Vector3()
 {
	 safeDelete(m_Vec);
 }

}