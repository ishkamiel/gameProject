#ifndef PLANE_H_
#define PLANE_H_

#include <math/Vector3_fwd.h>

namespace pdEngine
{

class Plane
{
	friend inline bool operator==(const Plane& lhs, const Plane& rhs) noexcept;
	friend inline bool operator!=(const Plane& lhs, const Plane& rhs) noexcept;

public:
	Plane(const Plane&);
	Plane(Plane&&);
    Plane(float x, float y, float z, float d);
    Plane(const Vector3& point, const Vector3& normal);
    Plane(const Vector3& a, const Vector3& b, const Vector3& c);
    virtual ~Plane();

	Plane& operator=(const Plane&) noexcept;
	Plane& operator=(Plane&&) noexcept;

    inline const Vector3& getNormal(void) const noexcept;
    inline float getDistance(void) const noexcept;

    inline float distanceTo(const Vector3& point) const noexcept;
    inline bool isOn(const Vector3& point) const noexcept;
    inline bool isInside(const Vector3& point) const noexcept;


private:
	Vector3 n;
	float d;
};




}
#endif /* PLANE_H_ */
