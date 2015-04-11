/*
 * Matrix4.cpp
 *
 *  Created on: Apr 10, 2015
 *      Author: ishkamiel
 */

#include "math/Matrix4.h"

namespace pdEngine
{

Matrix4::Matrix4()
{}

Matrix4::Matrix4(const Matrix4& m)
: glm::mat4(m)
{}

Matrix4::Matrix4(Matrix4&& m)
: glm::mat4(m)
{}

Matrix4::Matrix4(const glm::mat4& m)
: glm::mat4(m)
{}

Matrix4::Matrix4(glm::mat4&& m)
: glm::mat4(m)
{}

Matrix4::~Matrix4()
{}

Matrix4& Matrix4::operator=(const Matrix4&) = default;
Matrix4& Matrix4::operator=(Matrix4&&) = default;

}
