#include "renderer/SceneNodeProperties.h"

namespace pdEngine {

void SceneNodeProperties::setAlpha(const float alpha)
{
    m_AlphaType = AlphaMaterial;
    m_Material.setAlpha(alpha);
}

}
