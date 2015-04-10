/*
 * Matrix4.h
 *
 *  Created on: Apr 10, 2015
 *      Author: ishkamiel
 */

#ifndef SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_MATRIX4_H_
#define SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_MATRIX4_H_

#include <glm/mat4.hpp>

namespace pdEngine
{

class Matrix4 : public glm::mat4
{
	Matrix4();
	~Matrix4();
};

}

#endif /* SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_MATRIX4_H_ */
