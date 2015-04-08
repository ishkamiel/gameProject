#ifndef PLANE_H_
#define PLANE_H_

#include <math/Vector3_fwd.h>
//#include <glm/fwd.hpp>

namespace pdEngine
{

class Plane
{
public:
	Plane(const Plane&);
	Plane(Plane&&);
    Plane(float x, float y, float z, float d);
    Plane(const Vector3& point, const Vector3& normal);
    Plane(const Vector3& a, const Vector3& b, const Vector3& c);
    virtual ~Plane();

	Plane& operator=(const Plane&) noexcept;
	Plane& operator=(Plane&&) noexcept;

    inline bool isOn(const Vector3& point) const noexcept;
    inline bool isInside(const Vector3& point) const noexcept;

	inline bool operator==(const Plane&) const noexcept;
	inline bool operator!=(const Plane&) const noexcept;

private:
	Vector3 n;
	float d;
};




}
#endif /* PLANE_H_ */
