#ifndef FRUSTUM_H_
#define FRUSTUM_H_

#include <glm/fwd.hpp>

namespace pdEngine
{

using vec3 = glm::vec3;

class Frustum
{
public:
    Frustum ();
    virtual ~Frustum ();

    bool isInside(const vec3& point) const;
    bool isInside(const vec3& point, const float radius) const;

    void init(void);

    void setFov(float);
    void setNear(float);
    void setFar(float);


private:

    vec3* m_ClipNear;
    vec3* m_ClipFar;

    float m_Fov;
    float m_Aspect;
    float m_Near;
    float m_Far;
};

}

#endif /* FRUSTUM_H_ */
