#include "math/Frustum.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace pdEngine
{

Frustum::Frustum()
    : m_VFov(glm::pi<float>()/2.0f), m_Aspect(1.0f), m_Near(1.0f), m_Far(10000.0f)
{
    init();
}

Frustum::Frustum(const float fov, const float aspect, const float near, const float far)
    : m_VFov(fov), m_Aspect(aspect), m_Near(near), m_Far(far)
{
    init();
}


Frustum::~Frustum()
{}

Matrix4 Frustum::getPerspective(void) const noexcept
{
    float hFov = m_VFov/m_Aspect;
    float left = m_Near*static_cast<float>(tan(hFov/2.f));
    float right = left;
    float top = m_Near*static_cast<float>(tan(m_VFov/2.f));
    float bottom = top;

    return glm::frustum(left, right, bottom, top, m_Near, m_Far);
}

void Frustum::init(void) noexcept
{
    //float z_dir = (m_Near-m_Far) / std::abs(m_Near-m_Far);

	float diff = m_Far - m_Near;
	float depth_dir = diff/ std::abs(diff);

    float x = static_cast<float>(cos(m_VFov/m_Aspect)) / 2.0f;
    float hz = (-depth_dir) * static_cast<float>(sin(m_VFov/m_Aspect)) / 2.0f;
    float y = static_cast<float>(cos(m_VFov/2.0f));
    float vz = (-depth_dir) * static_cast<float>(sin(m_VFov/2.0f));

    assert(m_Near != 0.0f || m_Far != 0.0f);
	assert(std::abs(m_Far) > std::abs(m_Near));
    assert(x == x);
    assert(y==y);
    assert(hz==hz);
    assert(vz==vz);

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
