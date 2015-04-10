/* 
 * File:   Vector3_fwd.h
 * Author: ishkamiel
 *
 * Created on April 8, 2015, 3:12 PM
 */

#ifndef VECTOR3_FWD_H
#define	VECTOR3_FWD_H

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

#include <memory>
#include <ostream>

namespace pdEngine
{

class Vector3 : public glm::vec3
{
    // friend inline bool operator==(const Vector3& lhs, const Vector3& rhs) noexcept;
    // friend inline bool operator!=(const Vector3& lhs, const Vector3& rhs) noexcept;
    friend inline float dot (const Vector3& lhs, const Vector3& rhs) noexcept;

    friend inline Vector3 operator*(const Vector3& lhs, const float) noexcept;
    friend inline Vector3& operator*=(Vector3& lhs, const float) noexcept;
    friend inline Vector3 operator*(const Vector3& lhs, const int) noexcept;
    friend inline Vector3& operator*=(Vector3& lhs, const int) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Vector3& plane) noexcept;

public:
    Vector3(void);
    Vector3(const float, const float, const float);
    Vector3(const Vector3&);
    Vector3(Vector3&&);
    Vector3(const glm::vec3&);

    virtual ~Vector3();

	inline float getX(void) const noexcept;
	inline float getY(void) const noexcept;
	inline float getZ(void) const noexcept;

	inline float length(void) const noexcept;

    inline Vector3& normalize(void) noexcept;
    inline Vector3 getNormalized(void) const noexcept;

	inline Vector3& operator=(const Vector3&) noexcept;
	inline Vector3& operator=(Vector3&&) noexcept;

private:
    //std::unique_ptr<glm::vec3> m_Vec;
};

}
#endif	/* VECTOR3_FWD_H */

