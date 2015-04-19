/*
 * Vector4.h
 *
 *  Created on: Apr 10, 2015
 *      Author: ishkamiel
 */

#ifndef SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_VECTOR4_H_
#define SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_VECTOR4_H_

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>

namespace pdEngine
{

class Vector4 : public glm::vec4
{
public:
	Vector4();
	Vector4(const float, const float, const float, const float);
	virtual ~Vector4();
};

}
#endif /* SOURCE_DIRECTORY__ENGINE_INCLUDE_MATH_VECTOR4_H_ */
