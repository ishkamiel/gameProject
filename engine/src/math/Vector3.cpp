#include "math/Vector3.h"

#include "Utils.h"

#include <glm/vec3.hpp>

namespace pdEngine
{

Vector3::Vector3(void)
: glm::vec3()
{}

Vector3::Vector3(const float x, const float y, const float z)
: glm::vec3(x, y, z)
{}

Vector3::Vector3(const Vector3& vec)
: glm::vec3(vec.x, vec.y, vec.z)
{}

Vector3::Vector3(Vector3&& vec) = default;

Vector3::Vector3(const glm::vec3& vec)
: glm::vec3(vec)
{}


Vector3::~Vector3()
{}

std::ostream& operator<<(std::ostream& os, const Vector3& v) noexcept
{
    return (os << "(" << v.x << ", " << v.y << ", " << v.z << ")");
}

}
