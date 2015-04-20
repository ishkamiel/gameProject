#ifndef SCENENODE_H_
#define SCENENODE_H_

#include "renderer/I_SceneNode.h"
#include "renderer/RenderPass.h"
#include "renderer/Material.h"
#include "math/Matrix4.h"
#include "math/Vector3.h"
#include "actors/Actor.h"
#include "Color.h"

#include <string>
#include <vector>

namespace pdEngine {

class SceneNode : public I_SceneNode
{
    friend class Scene;

    using SceneNodeList = std::vector<SceneNode_sptr>;

public:
    SceneNode (ActorId, std::string , RenderPass , const Color&, const Matrix4&);
    SceneNode (ActorId, std::string , RenderPass , const Color&, const Matrix4&, const Matrix4&);
    virtual ~SceneNode();

    virtual void v_setTransform(const Matrix4& toWrold, const Matrix4& fromWorld) noexcept override;
    virtual void v_setTransform(const Matrix4& toWorld) noexcept override;

    virtual bool v_OnRestore(Scene* scene) override;
    virtual bool v_OnUpdate(Scene* scene, const int) override;

    virtual bool v_IsVisible(Scene*) const override;

    virtual bool v_PreRender(Scene*) override;
    virtual bool v_Render(Scene* scene) override;
    virtual bool v_PostRender(Scene* scene) override;

    virtual bool v_RenderChildren(Scene* scene) override;

    virtual bool v_AddChild(std::shared_ptr<I_SceneNode>) override;
    virtual bool v_RemoveChild(ActorId id) override;

    virtual inline void setAlpha(const float alpha);
    inline void setPosition(const Vector3 &pos);
    inline void setRadius(const float radius);
    inline void setMaterial(const Material &mat);

    Vector3 getDirection(const Vector3 &pos) const;
    virtual const Vector3 getPosition() const override;

    virtual inline const ActorId& getActorID() const override;
    virtual inline const Matrix4& getToWorld() const override;
    virtual inline const Matrix4& getFromWorld() const override;
    virtual inline const char* getName() const override;
    virtual inline bool hasAlpha() const override;
    virtual inline float getAlpha() const override;
    virtual inline void getTransform(Matrix4* toWorld, Matrix4* fromWorld) const override;
    virtual inline RenderPass getRenderPass() const override;
    virtual inline float getRadius() const override;
    virtual inline const Material& getMaterial() const override;
protected:

protected:
    ActorId m_ActorID;
    std::string m_Name;
    float m_Radius;
    RenderPass m_RenderPass;
    AlphaType m_AlphaType;
    Matrix4 m_ToWorld;
    Matrix4 m_FromWorld;
    Material m_Material;

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

auto SceneNode::getActorID() const -> const ActorId&
{ 
    return m_ActorID; 
}

auto SceneNode::getToWorld() const -> const Matrix4&
{ 
    return m_ToWorld; 
}

auto SceneNode::getFromWorld() const -> const Matrix4&
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

void SceneNode::getTransform(Matrix4* toWorld, Matrix4* fromWorld) const
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
