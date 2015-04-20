#include "renderer/RootNode.h"

#include "renderer/SceneNode.h"
#include "renderer/RenderPass.h"

namespace pdEngine
{
static const Matrix4 identity = Matrix4();

RootNode::RootNode()
    : SceneNode(0, "Root", RenderPass::First, Color(), Matrix4())
{
    m_Children.reserve(static_cast<long>(RenderPass::Last));

    rootStatic.reset(new SceneNode(
                NullActorID, "StaticGroup", RenderPass::Static,
                Color(), Matrix4()));

    rootActor.reset(new SceneNode(
                NullActorID, "ActorGroup", RenderPass::Actor,
                Color(), Matrix4()));

    rootSky.reset(new SceneNode(
                NullActorID, "SkyGroup", RenderPass::Sky,
                Color(), Matrix4()));

    rootInvisible.reset(new SceneNode(
                NullActorID, "InvisibleGroup", RenderPass::NotRendered,
                Color(), Matrix4()));
}

RootNode::~RootNode()
{
    // TODO
}

bool RootNode::v_IsVisible(Scene* scene) const
{
	return true;
}

bool RootNode::v_AddChild(SceneNode_sptr child)
{
    switch(child->getRenderPass())
    {
        case RenderPass::Static:
            rootStatic->v_AddChild(child);
            break;
        case RenderPass::Actor:
            rootActor->v_AddChild(child);
            break;
        case RenderPass::Sky:
            rootSky->v_AddChild(child);
            break;
        case RenderPass::NotRendered:
            rootSky->v_AddChild(child);
            break;
        default:
            assert("Hmm, maybe we should implement this " && static_cast<int>(child->getRenderPass()));
    }
    return true;
}

bool RootNode::v_RenderChildren(Scene* scene)
{
    rootStatic->v_RenderChildren(scene);
    rootActor->v_RenderChildren(scene);

    // FIXME
    //rootSky->v_RenderChildren(scene);

    return true;
}

}
