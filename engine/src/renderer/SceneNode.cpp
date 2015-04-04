#include "renderer/SceneNode.h"

namespace pdEngine 
{

SceneNode::SceneNode (ActorID actorID,
            std::string name,
            RenderPass renderPass,
            const Color &diffuseColor,
            const mat4 *to,
            const mat4 *from)
{
    m_ActorID = actorID;
    m_Name = name;
    m_RenderPass = renderPass;
    m_Radius = 0;
    m_AlphaType = AlphaType::Opaque;

    v_SetTransform(to, from);
    m_Material.setDiffuse(diffuseColor);
}

SceneNode::~SceneNode()
{}



}
