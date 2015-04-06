#include "renderer/Color.h"

#include <glm/mat4x4.hpp>

namespace pdEngine 
{

Color::Color(float r, float g, float b, float a)
: m_Vec(new glm::vec4(r, g, b, a))
{}

Color::~Color()
{
	delete m_Vec;
}

float Color::getR(void) const
{
	return (*m_Vec)[0];
}

float Color::getG(void) const
{
	return (*m_Vec)[1];
}

float Color::getB(void) const
{
	return (*m_Vec)[2];
}

float Color::getA(void) const
{
	return (*m_Vec)[3];
}

void Color::setR(float r)
{
	(*m_Vec)[0] = r;
}

void Color::setG(float g)
{
	(*m_Vec)[1] = g;
}

void Color::setB(float b)
{
	(*m_Vec)[2] = b;
}

void Color::setA(float a)
{
	(*m_Vec)[3] = a;
}

const glm::vec4& Color::getVector(void) const
{
	return *m_Vec;
}

}