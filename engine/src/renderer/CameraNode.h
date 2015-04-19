#ifndef CAMERA_H_
#define CAMERA_H_

#include "renderer/SceneNode.h"
#include "actors/Actor.h"
#include "math/Frustum.h"
#include "math/Matrix4.h"
#include "math/Vector4.h"

namespace pdEngine
{

class CameraNode : public SceneNode
{

public:
    CameraNode(const Matrix4*, const Frustum&);
    virtual ~CameraNode();

    virtual bool v_Render(Scene*) override;
    virtual bool v_OnRestore(Scene*) override;
    virtual bool v_IsVisible(Scene*) const override;

    virtual bool v_SetView(Scene*);

    const Frustum& getFrustum(void);

    void setTarget(SceneNode_sptr);
    void clearTarget(void);
    SceneNode_sptr getTarget(void);

    Matrix4 getWorldViewProjection(Scene*);

    Matrix4 getProjection();
    Matrix4 getView();

    void setCameraOffset(const Vector4&);

protected:

    Frustum m_Frustum;
    Matrix4 m_Projection;
    Matrix4 m_View;
    bool m_IsActive;
    bool m_DebugCamera;
    SceneNode_sptr m_Target;
    Vector4 m_CamOffsetVector;
};

}
#endif /* CAMERA_H_ */
