#include "renderer/Material.h"

#include "utils/Logger.h"

namespace pdEngine {

Material::Material()
{}

Material::~Material()
{}

void Material::setDiffuse(const Color& color)
{
	(void)color;
	PDE_WARN << "Material::setDiffuse not implemented";
}

bool Material::hasAlpha() const
{
	PDE_WARN << "Material::hasAlpha not implemented";
	return false;
}

float Material::getAlpha() const
{
	PDE_WARN << "Material::getAlpha not implemented";
	return 0.0f;
}

void Material::setAlpha(const float alpha)
{
	PDE_WARN << "Material::setAlpha not implemented";
	(void)alpha;
}

}