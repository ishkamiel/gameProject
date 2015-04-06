#include "renderer/CameraNode.h"

#include <glm/mat4x4.hpp>
#include <glm/matrix.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

namespace pdEngine
{

CameraNode::CameraNode(const glm::mat4* t, const Frustum& frustum)
   : SceneNode(NullActorID, "Camera", RenderPass::First, Color(), t),
   m_Frustum(frustum),
   m_IsActive(true),
   m_DebugCamera(false),
   //m_pTarget(),
   m_CamOffsetVector( 0.0f, 1.0f, -10.0f, 0.0f )
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

bool CameraNode::v_SetView(Scene* scene)
{
    (void)scene;
    auto mat = m_Target->getToWorld();
    auto at = m_CamOffsetVector;
    auto atWorld = glm::translate(mat, glm::vec3(at));

    auto lookAt = glm::lookAt(
            glm::vec3(glm::row(atWorld, 3)), 
            glm::vec3(at), 
            glm::vec3(0.0f,1.0f,0.0f));

    v_SetTransform(&lookAt);
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

auto CameraNode::getWorldViewProjection(Scene*) -> glm::mat4
{
    return m_Projection;
}

auto CameraNode::getProjection() -> glm::mat4
{ 
    return m_Projection; 
}

auto CameraNode::getView() -> glm::mat4
{ 
    return m_View; 
}

void CameraNode::setCameraOffset(const vec4&)
{
}

}
