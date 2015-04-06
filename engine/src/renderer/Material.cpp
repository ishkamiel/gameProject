#include "renderer/Material.h"

#include "Logger.h"

namespace pdEngine {

Material::Material()
{}

Material::~Material()
{}

void Material::setDiffuse(const Color& color)
{
	DLOG("Material::setDiffuse not implemented");
	(void)color;
}

bool Material::hasAlpha() const
{
	DLOG("Material::hasAlpha not implemented");
	return false;
}

float Material::getAlpha() const
{
	DLOG("Material::getAlpha not implemented");
	return 0.0f;
}

void Material::setAlpha(const float alpha)
{
	DLOG("Material::setAlpha not implemented");
	(void)alpha;
}

}