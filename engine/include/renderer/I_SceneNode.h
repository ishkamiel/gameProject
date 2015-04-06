#ifndef I_SCENENODE_H_
#define I_SCENENODE_H_

#include "renderer/Scene.h"
#include "renderer/RenderPass.h"
#include "renderer/Material.h"
#include "Actor.h"
#include "Timer.h"

#include <glm/fwd.hpp>

#include <memory>

namespace pdEngine {

class I_SceneNode
{
    using mat4 = glm::mat4;
    using vec3 = glm::vec3;

public:
    virtual ~I_SceneNode() {};

    virtual void v_SetTransform(const mat4* toWorld, const mat4* fromWorld = nullptr) = 0;

    virtual bool v_OnRestore(Scene*) = 0;
    virtual void v_OnUpdate(Scene*, const TimeMicro) = 0;

    virtual bool v_IsVisible(Scene*) const = 0;

    virtual bool v_PreRender(Scene*) = 0;
    virtual bool v_Render(Scene*) = 0;
    virtual bool v_PostRender(Scene*) = 0;

    virtual bool v_RenderChildren(Scene*) = 0;

    virtual bool v_AddChild(std::shared_ptr<I_SceneNode>) = 0;
    virtual bool v_RemoveChild(ActorID id) = 0;

    // Accessors
    virtual const vec3 getPosition() const = 0;
    virtual const ActorID& getActorID() const = 0;
    virtual const mat4& getToWorld() const = 0;
    virtual const mat4& getFromWorld() const = 0;
    virtual const char* getName() const = 0;
    virtual bool hasAlpha() const = 0;
    virtual float getAlpha() const = 0;
    virtual void getTransform(mat4* toWorld, mat4* fromWorld) const = 0;
    virtual RenderPass getRenderPass() const = 0;
    virtual float getRadius() const = 0;
    virtual const Material& getMaterial() const = 0;
};

using SceneNode_sptr = std::shared_ptr<I_SceneNode>;

}
#endif /* I_SCENENODE_H_ */
