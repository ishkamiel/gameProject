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

namespace pdEngine
{

class Matrix4 : public glm::mat4
{
public:
	Matrix4();
	Matrix4(const Matrix4&);
	Matrix4(Matrix4&&);
	virtual ~Matrix4();

	Matrix4& operator=(const Matrix4&);
	Matrix4& operator=(Matrix4&&);

	Matrix4 getInverse(void) const noexcept;
	Matrix4 getTranslated(const Vector4&) const noexcept;
};

}

#endif /* SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_MATRIX4_H_ */
