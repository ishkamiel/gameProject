#pragma once

#include "renderer/Scene.h"
#include "renderer/RenderPass.h"
#include "renderer/Material.h"
#include "math/Matrix4.h"
#include "math/Vector3.h"
#include "actors/Actor.h"

#include <memory>

namespace pdEngine {

class I_SceneNode
{

public:
    virtual ~I_SceneNode() {};

    virtual void v_setTransform(const Matrix4& toWorld, const Matrix4& fromWorld) noexcept = 0;
    virtual void v_setTransform(const Matrix4& toWorld) noexcept = 0;

    virtual bool v_OnRestore(Scene*) = 0;
    virtual bool v_OnUpdate(Scene*, const int) = 0;

    virtual bool v_IsVisible(Scene*) const = 0;

    virtual bool v_PreRender(Scene*) = 0;
    virtual bool v_Render(Scene*) = 0;
    virtual bool v_PostRender(Scene*) = 0;

    virtual bool v_RenderChildren(Scene*) = 0;

    virtual bool v_AddChild(std::shared_ptr<I_SceneNode>) = 0;
    virtual bool v_RemoveChild(ActorID id) = 0;

    // Accessors
    virtual const Vector3 getPosition() const = 0;
    virtual const ActorID& getActorID() const = 0;
    virtual const Matrix4& getToWorld() const = 0;
    virtual const Matrix4& getFromWorld() const = 0;
    virtual const char* getName() const = 0;
    virtual bool hasAlpha() const = 0;
    virtual float getAlpha() const = 0;
    virtual void getTransform(Matrix4* toWorld, Matrix4* fromWorld) const = 0;
    virtual RenderPass getRenderPass() const = 0;
    virtual float getRadius() const = 0;
    virtual const Material& getMaterial() const = 0;
};

using SceneNode_sptr = std::shared_ptr<I_SceneNode>;

}
