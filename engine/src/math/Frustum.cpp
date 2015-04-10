#include "math/Frustum.h"

#include "Utils.h"

#include "math/Plane.h"
#include "Logger.h"

#include <glm/gtc/constants.hpp>

namespace pdEngine
{

Frustum::Frustum()
    : m_Fov(glm::pi<float>()/2.0f), m_Aspect(1.0f), m_Near(1.0f), m_Far(10000.0f)
{
    init();
}

Frustum::Frustum(const float fov, const float aspect, const float near, const float far)
    : m_Fov(fov), m_Aspect(aspect), m_Near(near), m_Far(far)
{
    init();
}


Frustum::~Frustum()
{}

void Frustum::init(void) noexcept
{
    //float z_dir = (m_Near-m_Far) / std::abs(m_Near-m_Far);

	float diff = m_Far - m_Near;
	float depth_dir = diff/ std::abs(diff);

    float x = cos((m_Fov/m_Aspect)/2.0f);
    float hz = (-depth_dir) * sin((m_Fov/m_Aspect)/2.0f);
    float y = cos(m_Fov/2.0f);
    float vz = (-depth_dir) * sin(m_Fov/2.0f);

    assert((m_Near != 0.0f || m_Far != 0.0f) && "zero depth frustum");
	assert(std::abs(m_Far) > std::abs(m_Near) && "bad Far and Near clips");
    assert((x == x && y==y && hz==hz && vz==vz) && "something is NaN");

    m_Planes.reserve(6);
    m_Planes.emplace_back(0, 0, -depth_dir, m_Near);
    m_Planes.emplace_back(0, 0, depth_dir, std::abs(m_Far));
    m_Planes.emplace_back(0.0f, y, vz, 0.0f); // upper
    m_Planes.emplace_back(0.0f, -y, vz, 0.0f); // lower
    m_Planes.emplace_back(x, 0.0f, hz, 0.0f); // sides
    m_Planes.emplace_back(-x, 0.0f, hz, 0.0f);
}

std::ostream& operator<<(std::ostream& os, const Frustum& f) noexcept
{
    for (auto p : f.m_Planes)
        os << p;

    return os;
}

}
