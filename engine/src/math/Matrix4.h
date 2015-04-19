/*
 * Matrix4.h
 *
 *  Created on: Apr 10, 2015
 *      Author: ishkamiel
 */

#ifndef SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_MATRIX4_H_
#define SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_MATRIX4_H_

#include "math/Vector4.h"

#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>

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
	inline Matrix4 getTranslated(const Vector4&) const noexcept;
};

Matrix4 Matrix4::getInverse(void) const noexcept
{
	return Matrix4(glm::inverse(static_cast<glm::mat4>(*this)));
}


}

#endif /* SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_MATRIX4_H_ */
