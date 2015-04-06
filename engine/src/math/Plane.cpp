#include "math/Plane.h"

#include "Utils.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vector_relational.hpp>

namespace pdEngine
{

Plane::Plane (float x, float y, float z, float d)
    : m_Vec(new Vector4(x, y, z, d))
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
{
    safeDelete(m_Vec);
}

bool Plane::isOn(const Vector3& point) const
{
}

bool Plane::isInside(const Vector3& point) const
{
}

bool Plane::operator==(const Plane& other)
{ 
    return (*other.m_Vec == *m_Vec);
}

}
