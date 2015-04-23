#pragma once

#include<glm/vec3.hpp>
#include<glm/geometric.hpp>

#include<ostream>

namespace pdEngine
{

class Vector3 : public glm::vec3
{
    friend inline float dot (const Vector3& lhs, const Vector3& rhs) noexcept;
    friend inline Vector3 cross (const Vector3& lhs, const Vector3& rhs) noexcept;

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

    inline float getX(void) const noexcept __attribute__ ((deprecated));
    inline float getY(void) const noexcept __attribute__ ((deprecated));
	inline float getZ(void) const noexcept __attribute__ ((deprecated));

	//inline float length(void) const noexcept;

    inline Vector3& normalize(void) noexcept;
    inline Vector3 getNormalized(void) const noexcept;

	inline Vector3& operator=(const Vector3&) noexcept;
	inline Vector3& operator=(Vector3&&) noexcept;
};

float Vector3::getX(void) const noexcept
{
    return x;
}

float Vector3::getY(void) const noexcept
{
    return y;
}

float Vector3::getZ(void) const noexcept
{
    return z;
}

/*
float Vector3::length(void) const noexcept
{
    return glm::length(static_cast<glm::vec3>(*this));
}
 */

Vector3& Vector3::normalize(void) noexcept
{
    if ( x != 0.0f || y != 0.0f || z != 0.0f)
    {
        (*this) = glm::normalize(static_cast<glm::vec3>(*this));
    	//this = glm::normalize(this);
    }
    return *this;
}

inline Vector3 Vector3::getNormalized(void) const noexcept
{
    if (x == 0.0f && y == 0.0f && z == 0.0f)
        return Vector3(0.0f, 0.0f, 0.0f);

    return Vector3(glm::normalize(static_cast<glm::vec3>(*this)));
}

inline Vector3& Vector3::operator=(const Vector3& o) noexcept
{
    x  = o.x;
    y  = o.y;
    z  = o.z;
    return *this;
}

inline Vector3& Vector3::operator=(Vector3&& o) noexcept
{
    x  = o.x;
    y  = o.y;
    z  = o.z;
    return *this;
}

inline float dot (const Vector3& l, const Vector3& r) noexcept
{
    return glm::dot(static_cast<glm::vec3>(l), static_cast<glm::vec3>(r));
}

inline Vector3 cross (const Vector3& l, const Vector3& r) noexcept
{
    return Vector3(glm::cross(l, r));
}

inline Vector3 operator*(const Vector3& l, const float s) noexcept
{
    return Vector3(l.x*s, l.y*s, l.z*s);
}

inline Vector3& operator*=(Vector3& l, const float s) noexcept
{
    l.x *= s;
    l.y *= s;
    l.z *= s;
    return l;
}

inline Vector3 operator*(const Vector3& l, const int s) noexcept
{
    return (l*static_cast<float>(s));
}

inline Vector3& operator*=(Vector3& l, const int s) noexcept
{
    return (l *= static_cast<float>(s));
}

}
