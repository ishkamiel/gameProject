#include "renderer/Scene.h"

#include "renderer/RootNode.h"
#include "renderer/CameraNode.h"
#include "Timer.h"

#include <cassert>

namespace pdEngine
{

Scene::Scene(I_Renderer* renderer)
: m_Renderer(renderer)
{
    m_Root.reset(new RootNode());
    //m_LightManager.reset(new LightManager);
    m_TranlsationMatrices.push(Matrix4());
}

Scene::~Scene()
{
    m_Root.reset();
    m_LightManager.reset();
    while (!m_TranlsationMatrices.empty()) m_TranlsationMatrices.pop();
}

bool Scene::onRender(void) 
{
    if (m_Root && m_Camera)
    {
        //m_Camera->getViewTransform(this);
        m_Renderer->setProjection(m_Camera->getProjection());
        m_Renderer->setView(m_Camera->getView());
        // m_LightManager->CalcLighting(this);

        if (m_Root->v_PreRender(this))
        {
            m_Root->v_Render(this);
            m_Root->v_RenderChildren(this);
            m_Root->v_PostRender(this);
        }
    }

    // RenderAlphaPass();

    return true;
}

bool Scene::onRestore(void)
{
    if (!m_Root) return true;

    return m_Root->v_OnRestore(this);
}

bool Scene::onLostDevice(void)
{
    throw std::runtime_error("FIXME: Not implemented");
}

bool Scene::onUpdate(int delta)
{
    if (!m_Root) return true;

    return m_Root->v_OnUpdate(this, delta);
}

std::shared_ptr<I_SceneNode> Scene::findActor(ActorID id)
{
    auto i = m_ActorMap.find(id);

    if (i == m_ActorMap.end()) return nullptr;

    return i->second;
}

bool Scene::addChild(ActorID id, std::shared_ptr<I_SceneNode> child)
{
    m_ActorMap[id] = child;
    return m_Root->v_AddChild(child);

    // FIXME
    // shared_ptr<LightNode> pLight = dynamic_pointer_cast<LightNode>(kid);
    // if (pLight != NULL &&
    //         m_LightManager->m_Lights.size()+1 < MAXIMUM_LIGHTS_SUPPORTED)
    // {
    //     m_LightManager->m_Lights.push_back(pLight);
    // }
}

bool Scene::removeAChild(ActorID id)
{
    auto child = findActor(id);

    m_ActorMap.erase(id);
    return m_Root->v_RemoveChild(id);

    // if (id == INVALID_ACTOR_ID)
    //     return false;
    //
    // shared_ptr<ISceneNode> kid = FindActor(id);
    // shared_ptr<LightNode> pLight = dynamic_pointer_cast<LightNode>(kid);
    // if (pLight != NULL)
    //     m_LightManager->m_Lights.remove(pLight);
    //
    // m_ActorMap.erase(id);
    // return m_Root->VRemoveChild(id);
}

void Scene::setCamera(CameraNode_sptr)
{
}

const CameraNode_sptr Scene::getCamera(void) const
{
    return m_Camera;
}

void Scene::pushMatrix(const Matrix4* toWorld)
{
    m_TranlsationMatrices.push(*toWorld);

    // FIXME
    // m_MatrixStack->Push();
    // m_MatrixStack->MultMatrixLocal(&toWorld);
    // DXUTGetD3DDevice()->SetTransform(D3DTS_WORLD, m_MatrixStack->GetTop());
}

void Scene::popMatrix(void)
{
    m_TranlsationMatrices.pop();

    // FIXME
    // DXUTGetD3DDevice()->SetTransform(D3DTS_WORLD, m_MatrixStack->GetTop());
}

const Matrix4* Scene::getTopMatrix(void)
{
    return &(m_TranlsationMatrices.top());
}

LightManager_sptr Scene::getLightManager()
{
    return m_LightManager;
}

}
