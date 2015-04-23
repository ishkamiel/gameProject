#include "renderer/CameraNode.h"
#include "renderer/SceneNode.h"

#define GLM_FORCE_RADIANS

namespace pdEngine
{

CameraNode::CameraNode(const Matrix4& t, const Frustum& frustum)
   : SceneNode(NullActorId, "Camera", RenderPass::First, Color(), t),
   m_Frustum(frustum),
   m_IsActive(true),
   m_DebugCamera(false)
   //m_pTarget(),
   //m_CamOffsetVector( 0.0f, 1.0f, -10.0f, 0.0f )
{}

CameraNode::~CameraNode()
{
}

bool CameraNode::v_Render(Scene*)
{
    // TODO
    //if (m_DebugCamera) m_Frustum.Render();
    return true;
}

bool CameraNode::v_OnRestore(Scene*)
{
    // TODO
    
    // m_Frustum.SetAspect(DXUTGetWindowWidth() / (FLOAT) DXUTGetWindowHeight());
    // D3DXMatrixPerspectiveFovLH( &m_Projection, m_Frustum.m_Fov,
    //         m_Frustum.m_Aspect, m_Frustum.m_Near, m_Frustum.m_Far );
    // return S_OK;
    return true;
}

bool CameraNode::v_IsVisible(Scene*) const
{
    return m_IsActive;
}

bool CameraNode::v_setView(Scene* scene) noexcept
{
    (void)scene;
    /*
    auto mat = m_Target->getToWorld();
    auto atWorld = mat->getTranslated(m_CamOffsetVector);

    auto lookAt = Matrix4(glm::lookAt(
            glm::vec3(glm::row(atWorld, 3)), 
            glm::vec3(at), 
            glm::vec3(0.0f,1.0f,0.0f)));

    v_SetTransform(&lookAt);
    */
    return true;
}

auto CameraNode::getFrustum(void) -> const Frustum&
{
    return m_Frustum;
}

void CameraNode::setTarget(SceneNode_sptr target)
{
    m_Target = target;
}

void CameraNode::clearTarget(void)
{
    m_Target.reset();
}

auto CameraNode::getTarget(void) -> SceneNode_sptr
{
    return m_Target;
}

auto CameraNode::getWorldViewProjection(Scene*) -> Matrix4
{
    return getProjection() * getView();
    //return getProjection() * getView();
    //return m_Projection;
}

auto CameraNode::getProjection(void) noexcept -> Matrix4&
{ 
    return m_Projection;
}

auto CameraNode::getView(void) noexcept -> Matrix4&
{ 
    return m_View;
}
void CameraNode::setCameraOffset(const Vector4& v)
{
	(void)v;
}

}
