#ifndef FRUSTUM_H_
#define FRUSTUM_H_

#include "math/Vector3.h"
#include "math/Plane.h"

#include <ostream>
#include <vector>

namespace pdEngine
{

class Frustum
{
	friend std::ostream& operator<<(std::ostream& os, const Frustum& f) noexcept;

public:
	Frustum();
	Frustum(const float fov, const float aspect, const float near,
			const float far);
	virtual ~Frustum();

	inline bool isInside(const Vector3& point) const noexcept;
	inline bool isInside(const Vector3& point, const float radius) const
			noexcept;

	void setFov(float);
	void setNear(float);
	void setFar(float);

private:
	void init(void) noexcept;

	float m_Fov;
	float m_Aspect;
	float m_Near;
	float m_Far;

	std::vector<Plane> m_Planes;
};

bool Frustum::isInside(const Vector3 &p) const noexcept
{
	for (auto plane : m_Planes)
	{
		if (!plane.isInside(p))
		{
			return false;
		}
	}

	return true;
}

bool Frustum::isInside(const Vector3 &p, const float r) const noexcept
{
	for (auto plane : m_Planes)
		if (plane.distanceTo(p) > r)
			return false;

	return true;
}

}

#endif /* FRUSTUM_H_ */
