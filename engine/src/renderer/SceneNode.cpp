#include "renderer/SceneNode.h"

#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

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

void SceneNode::v_SetTransform(const mat4* toWorld, const mat4* fromWorld)
{
    m_ToWorld = *toWorld;
    if (!fromWorld)
        m_FromWorld = glm::inverse(*toWorld);
    else
        m_FromWorld = *fromWorld;
}

bool SceneNode::v_OnRestore(Scene* scene)
{
    auto i = m_Children.begin();
    auto end = m_Children.end();

    while (i != end)
    {
        (*i)->v_OnRestore(scene);
        ++i;
    }

    return true;
}

bool SceneNode::v_OnUpdate(Scene* scene, const TimeDelta delta)
{
    auto i = m_Children.begin();
    auto end = m_Children.end();
    while (i != end)
    {
        (*i)->v_OnUpdate(scene, delta);
        ++i;
    }

	return true;
}

bool SceneNode::v_PreRender(Scene* scene)
{
    scene->pushAndSetMatrix(&m_ToWorld);
    return true;
}

bool SceneNode::v_PostRender(Scene* scene)
{
    scene->popMatrix();
    return true;
}

bool SceneNode::v_Render(Scene* scene)
{
    (void)scene;
    return true;
}

bool SceneNode::v_IsVisible(Scene* scene) const
{
    glm::mat4 toWorld, fromWorld;
    auto camera = scene->getCamera();

    //FIXME

    //camera->getTransform(getTransform(&toWorld, &fromWorld));

    // glm::vec3 pos = getPosition();
    //
    // pos = fromWorld.Xform(pos);
    //
    // Frustum const &frustum = pScene->GetCamera()->GetFrustum();
    // return frustum.Inside(pos, VGet()->Radius());
    
    return true;
}

bool SceneNode::v_RenderChildren(Scene* scene)
{
    auto i = m_Children.begin();
    auto end = m_Children.end();

    while (i != end)
    {
        if ((*i)->v_PreRender(scene))
        {
            if ((*i)->v_IsVisible(scene))
            {
                if (!(*i)->hasAlpha()) 
                {
                    (*i)->v_Render(scene);
                }
                else if (m_AlphaType != AlphaType::Transparent)
                {
                    // FIXME
                    // The object isn’t totally transparent...
                    // AlphaSceneNode *asn = GCC_NEW AlphaSceneNode;
                    // assert(asn);
                    // asn->m_pNode = *i;
                    // asn->m_Concat = *pScene->GetTopMatrix();
                    //
                    // Vec4 worldPos(asn->m_Concat.GetPosition());
                    // Mat4×4 fromWorld = pScene->GetCamera()->VGet()->FromWorld();
                    // Vec4 screenPos = fromWorld.Xform(worldPos);
                    // asn->m_ScreenZ = screenPos.z;
                    //
                    // pScene->AddAlphaSceneNode(asn);
                }
            }

            (*i)->v_RenderChildren(scene);
        }
        (*i)->v_PostRender(scene);
        ++i;
    }

    return true;
}

bool SceneNode::v_AddChild(std::shared_ptr<I_SceneNode> child)
{
    m_Children.push_back(child);

    // The radius of the sphere should be fixed right here
    
    auto childPosition = child->getPosition();
    glm::vec3 direction = childPosition - getPosition();

    float newRadius = glm::length(direction) + child->getRadius();

    if (newRadius > m_Radius) m_Radius = newRadius;
    return true;
}

bool SceneNode::v_RemoveChild(ActorID id)
{
    auto i = m_Children.begin();
    auto end = m_Children.end();

    while (i != end)
    {
        if (id == (*i)->getActorID())
        {
            m_Children.erase(i);
            return true;
        }
        ++i;
    }
    return false;
}

void SceneNode::setPosition(const glm::vec3 &pos) 
{ 
    m_ToWorld[3][0] = pos[0];
    m_ToWorld[3][1] = pos[1];
    m_ToWorld[3][2] = pos[2];
}


auto SceneNode::getDirection(const glm::vec3 &pos) const -> glm::vec3
{ 
    // FIXME
    (void)pos;
    return glm::vec3();
}

auto SceneNode::getPosition() const -> const glm::vec3
{ 
    return glm::vec3(m_ToWorld[3][0], m_ToWorld[3][1], m_ToWorld[3][2]);
}

}
