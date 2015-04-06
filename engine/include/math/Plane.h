#ifndef PLANE_H_
#define PLANE_H_

#include <glm/fwd.hpp>

namespace pdEngine
{

using Vector3 = glm::vec3;
using Vector4 = glm::vec4;

class Plane
{
public:
    Plane(float x, float y, float z, float d);
    Plane(const Vector3& point, const Vector3& normal);
    Plane(const Vector3& a, const Vector3& b, const Vector3& c);
    virtual ~Plane();

    bool isOn(const Vector3& point) const;
    bool isInside(const Vector3& point) const;

    bool operator==(const Plane&);

private:
    glm::vec4* m_Vec;
};




}
#endif /* PLANE_H_ */
