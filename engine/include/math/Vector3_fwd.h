/* 
 * File:   Vector3_fwd.h
 * Author: ishkamiel
 *
 * Created on April 8, 2015, 3:12 PM
 */

#ifndef VECTOR3_FWD_H
#define	VECTOR3_FWD_H

#include <glm/fwd.hpp>

namespace pdEngine
{

class Vector3
{
public:
    Vector3(void);
    Vector3(const float, const float, const float);
    Vector3(const Vector3&);
    Vector3(Vector3&&);
    Vector3(const glm::vec3&);
    Vector3(glm::vec3&&);

    virtual ~Vector3();

	inline float getX(void) const noexcept;
	inline float getY(void) const noexcept;
	inline float getZ(void) const noexcept;

	inline float length(void) const noexcept;

    inline Vector3& normalize(void) noexcept;
    inline Vector3 getNormalized(void) noexcept;

	inline Vector3& operator=(const Vector3&) noexcept;
	inline Vector3& operator=(Vector3&&) noexcept;

private:
    glm::vec3* m_Vec;

public:

    friend inline bool operator==(const Vector3& lhs, const Vector3& rhs);
    friend inline bool operator!=(const Vector3& lhs, const Vector3& rhs);
};

}
#endif	/* VECTOR3_FWD_H */
