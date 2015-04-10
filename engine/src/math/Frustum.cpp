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
    PD_debug("Using a fov: {}", m_Fov);
    PD_debug("Using a apsect ratio: {}", m_Aspect);

    float z_dir = (m_Near-m_Far) / std::abs(m_Near-m_Far);

    float x = cos((m_Fov/m_Aspect)/2.0f);
    float zx = sin((m_Fov/m_Aspect)/2.0f) * z_dir;
    float y = cos(m_Fov/2.0f);
    float zy = sin(m_Fov/2.0f) * z_dir;

    PD_debug("{}/{}={}", m_Fov, m_Aspect, m_Fov/m_Aspect);
    PD_debug("acos({}/{})={}", m_Fov, m_Aspect, acos(m_Fov/m_Aspect));

    assert((m_Near != 0.0f || m_Far != 0.0f) && "cannot compute normals");
    assert((x == x && y==y && zx==zx && zy==zy) && "something is NaN");

    m_Planes.reserve(6);
    m_Planes.emplace_back(0, 0, z_dir, std::abs(m_Near));
    m_Planes.emplace_back(0, 0, -z_dir, std::abs(m_Far));
    m_Planes.emplace_back(0.0f, y, zy, 0.0f); // upper
    m_Planes.emplace_back(0.0f, -y, zy, 0.0f); // lower
    m_Planes.emplace_back(x, 0.0f, zx, 0.0f); // sides
    m_Planes.emplace_back(-x, 0.0f, zx, 0.0f);
}

std::ostream& operator<<(std::ostream& os, const Frustum& f) noexcept
{
    for (auto p : f.m_Planes)
        os << p;

    return os;
}

}
