#ifndef SCENENODE_H_
#define SCENENODE_H_

#include "renderer/I_SceneNode.h"
#include "renderer/RenderPass.h"
#include "renderer/Material.h"
#include "Actor.h"
#include "Color.h"

#include <glm/mat4x4.hpp>

#include <string>
#include <vector>

namespace pdEngine {

class SceneNode : public I_SceneNode
{
    friend class Scene;

    using mat4 = glm::mat4;
    using SceneNodeList = std::vector<I_SceneNode>;

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

    /*
       void SetAlpha(float alpha) { m_Props.SetAlpha(alpha); }
       float GetAlpha() const { return m_Props.Alpha(); }

       Vec3 GetPosition() const { return m_Props.m_ToWorld.GetPosition(); }
       void SetPosition(const Vec3 &pos) { m_Props.m_ToWorld.SetPosition(pos); }

       Vec3 GetDirection(const Vec3 &pos) const
       { return m_Props.m_ToWorld.GetDirection (pos); }

       void SetRadius(const float radius) { m_Props.m_Radius = radius; }
       void SetMaterial(const Material &mat) { m_Props.m_Material = mat; }
       */

    virtual inline const ActorID& getActorID() const override;
    virtual inline const mat4& getToWorld() const override;
    virtual inline const mat4& getFromWorld() const override;
    virtual inline const char* getName() const override;
    virtual inline bool hasAlpha() const override;
    virtual inline float getAlpha() const override;
    virtual inline void transform(mat4* toWorld, mat4* fromWorld) const override;
    virtual inline RenderPass getRenderPass() const override;
    virtual inline float getRadius() const override;
    virtual inline const Material& getMaterial() const override;
protected:
    virtual inline void setAlpha(const float alpha);

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

const char* SceneNode::getName() const
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

void SceneNode::transform(mat4* toWorld, mat4* fromWorld) const
{
    if (toWorld != nullptr)
        *toWorld = m_ToWorld;

    if (fromWorld != nullptr)
        *fromWorld = m_FromWorld;
}

RenderPass SceneNode::getRenderPass() const 
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
