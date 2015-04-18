#include "renderer/Material.h"

#include "Logger.h"

namespace pdEngine {

Material::Material()
{}

Material::~Material()
{}

void Material::setDiffuse(const Color& color)
{
	PD_debug("Material::setDiffuse not implemented");
	(void)color;
}

bool Material::hasAlpha() const
{
	PD_debug("Material::hasAlpha not implemented");
	return false;
}

float Material::getAlpha() const
{
	PD_debug("Material::getAlpha not implemented");
	return 0.0f;
}

void Material::setAlpha(const float alpha)
{
	PD_debug("Material::setAlpha not implemented");
	(void)alpha;
}

}