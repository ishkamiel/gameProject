#include "renderer/Frustum.h"

#include "Utils.h"

#include <glm/gtc/constants.hpp>
#include <glm/vec3.hpp>

namespace pdEngine
{

Frustum::Frustum()
{
    m_Fov = glm::pi<float>()/2.0;
    m_Aspect = 1.0f;
    m_Near = 1.0f;
    m_Far = 10000.0f;

    m_ClipFar = new glm::vec3[4];
    m_ClipNear = new glm::vec3[4];
}

Frustum::~Frustum()
{
    safeDeleteArray(m_ClipFar);
    safeDeleteArray(m_ClipNear);
}

bool Frustum::isInside(const glm::vec3 &point) const
{
  // for (int i=0; i<NumPlanes; ++i)
  // {
  //   if (!m_Planes[i].Inside(point))
  //     return false;
  // }
  //
  // return true;
   return true;
}

bool Frustum::isInside(const glm::vec3 &point, const float radius) const
{
  // for(int i = 0; i < NumPlanes; ++i)
  // {
  //   if (!m_Planes[i].Inside(point, radius))
  //     return false;
  // }
  //
  // // otherwise we are fully in view
  // return true;
    return true;
}

}
