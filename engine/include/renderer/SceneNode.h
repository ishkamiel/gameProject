#ifndef SCENENODE_H_
#define SCENENODE_H_

#include "renderer/I_SceneNode.h"
#include "renderer/RenderPass.h"
#include "renderer/Material.h"
#include "Actor.h"
#include "Color.h"

#include <glm/fwd.hpp>
#include <glm/mat4x4.hpp>
// #include <glm/vec3.hpp>

#include <string>
#include <vector>

namespace pdEngine {

class SceneNode : public I_SceneNode
{
    friend class Scene;

    using mat4 = glm::mat4;
    using vec3 = glm::vec3;

    using SceneNodeList = std::vector<SceneNode_sptr>;

public:
    SceneNode (ActorID actorID,
            std::string name,
            RenderPass renderPass,
            const Color &diffuseColor,
            const mat4 *to,
            const mat4 *from = nullptr);
    virtual ~SceneNode();

    virtual void v_SetTransform(const mat4* toWorld, const mat4* fromWorld = nullptr) override;

    virtual bool v_OnRestore(Scene* scene) override;
    virtual void v_OnUpdate(Scene* scene, const TimeMicro) override;

    virtual bool v_IsVisible(Scene* scene) override;

    virtual bool v_PreRender(Scene*) override;
    virtual bool v_Render(Scene* scene) override;
    virtual bool v_PostRender(Scene* scene) override;

    virtual bool v_RenderChildren(Scene* scene) override;

    virtual bool v_AddChild(std::shared_ptr<I_SceneNode>) override;
    virtual bool v_RemoveChild(ActorID id) override;

    virtual inline void setAlpha(const float alpha);
    void setPosition(const vec3 &pos);
    void setRadius(const float radius);
    void setMaterial(const Material &mat);

    vec3 getDirection(const vec3 &pos) const;
    virtual const vec3 getPosition() const override;

    virtual inline const ActorID& getActorID() const override;
    virtual inline const mat4& getToWorld() const override;
    virtual inline const mat4& getFromWorld() const override;
    virtual inline const char* getName() const override;
    virtual inline bool hasAlpha() const override;
    virtual inline float getAlpha() const override;
    virtual inline void getTransform(mat4* toWorld, mat4* fromWorld) const override;
    virtual inline RenderPass getRenderPass() const override;
    virtual inline float getRadius() const override;
    virtual inline const Material& getMaterial() const override;
protected:

protected:
    ActorID m_ActorID;
    std::string m_Name;
    glm::mat4 m_ToWorld;
    glm::mat4 m_FromWorld;
    float m_Radius;
    RenderPass m_RenderPass;
    Material m_Material;
    AlphaType m_AlphaType;

    SceneNodeList m_Children;
    SceneNode *m_Parent;
};

inline void SceneNode::setAlpha(const float alpha)
{
    m_Material.setAlpha(alpha);
}


void SceneNode::setRadius(const float radius) 
{ 
    m_Radius = radius; 
}

void SceneNode::setMaterial(const Material &mat) 
{ 
    m_Material = mat; 
}

auto SceneNode::getActorID() const -> const ActorID&
{ 
    return m_ActorID; 
}

auto SceneNode::getToWorld() const -> const mat4&
{ 
    return m_ToWorld; 
}

auto SceneNode::getFromWorld() const -> const mat4&
{ 
    return m_FromWorld; 
}

auto SceneNode::getName() const -> const char*
{ 
    return m_Name.c_str(); 
}

bool SceneNode::hasAlpha() const 
{ 
    return m_Material.hasAlpha(); 
}

float SceneNode::getAlpha() const 
{ 
    return m_Material.getAlpha(); 
}

void SceneNode::getTransform(mat4* toWorld, mat4* fromWorld) const
{
    if (toWorld != nullptr)
        *toWorld = m_ToWorld;

    if (fromWorld != nullptr)
        *fromWorld = m_FromWorld;
}

auto SceneNode::getRenderPass() const -> RenderPass
{ 
    return m_RenderPass; 
}

float SceneNode::getRadius() const 
{ 
    return m_Radius; 
}

const Material& SceneNode::getMaterial() const
{
    return m_Material;
}

}
#endif /* SCENENODE_H_ */
