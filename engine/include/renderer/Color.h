#ifndef COLOR_H_
#define COLOR_H_

#include <glm/fwd.hpp>

namespace pdEngine
{

class Color
{
public:
	Color(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
    virtual ~Color ();

	float getR(void) const;
	float getG(void) const;
	float getB(void) const;
	float getA(void) const;

	void setR(float);
	void setG(float);
	void setB(float);
	void setA(float);

	const glm::vec4& getVector(void) const;

private:
	glm::vec4* m_Vec;
};

}
#endif /* COLOR_H_ */
