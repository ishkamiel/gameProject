#ifndef CAMERA_H_
#define CAMERA_H_

#include "renderer/SceneNode.h"
#include "Actor.h"
#include "math/Frustum.h"

#include <glm/fwd.hpp>

namespace pdEngine
{

class CameraNode : public SceneNode
{
    using mat4 = glm::mat4;
    using vec4 = glm::vec4;


public:
    CameraNode(const glm::mat4*, const Frustum&);
    virtual ~CameraNode();

    virtual bool v_Render(Scene*) override;
    virtual bool v_OnRestore(Scene*) override;
    virtual bool v_IsVisible(Scene*) const override;

    virtual bool v_SetView(Scene*);

    const Frustum& getFrustum(void);

    void setTarget(SceneNode_sptr);
    void clearTarget(void);
    SceneNode_sptr getTarget(void);

    mat4 getWorldViewProjection(Scene*);

    mat4 getProjection();
    mat4 getView();

    void setCameraOffset(const vec4&);

protected:

    Frustum m_Frustum;
    mat4 m_Projection;
    mat4 m_View;
    bool m_IsActive;
    bool m_DebugCamera;
    SceneNode_sptr m_Target;
    vec4 m_CamOffsetVector;
};

}
#endif /* CAMERA_H_ */
