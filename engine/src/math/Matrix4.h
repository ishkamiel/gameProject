#pragma once

#include "math/Math_fwd.h"
#include "math/Vector3.h"

#define GLM_FORCE_RADIANS
#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace pdEngine
{

class Matrix4 : public glm::mat4
{
public:
	Matrix4();
	Matrix4(const Matrix4&);
	Matrix4(Matrix4&&);
	Matrix4(const glm::mat4&);
	Matrix4(glm::mat4&&);
	virtual ~Matrix4();

	Matrix4& operator=(const Matrix4&);
	Matrix4& operator=(Matrix4&&);

	inline Matrix4 getInverse(void) const noexcept;
	inline Matrix4 getTranslated(const Vector3&) const noexcept;
};

Matrix4 Matrix4::getInverse(void) const noexcept
{
	return Matrix4(glm::inverse(static_cast<glm::mat4>(*this)));
}

Matrix4 Matrix4::getTranslated(const Vector3& vec) const noexcept
{
	return Matrix4(glm::translate(
		static_cast<glm::mat4>(*this),
		static_cast<glm::vec3>(vec)));
}

}
