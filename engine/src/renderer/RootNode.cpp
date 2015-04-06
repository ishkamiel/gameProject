#include "renderer/RootNode.h"

#include "renderer/SceneNode.h"
#include "renderer/RenderPass.h"

#include <cstatic>

namespace pdEngine
{
static const glm::mat4 identity = glm::mat4();

RootNode::RootNode()
    : SceneNode(0, "Root", RenderPass::First, Color(), &identity)
{
    m_Children.reserve(static_cast<long>(RenderPass::Last));

    rootStatic.reset(new SceneNode(
                NullActorID, "StaticGroup", RenderPass::Static,
                Color(), &identity));

    rootActor.reset(new SceneNode(
                NullActorID, "ActorGroup", RenderPass::Actor,
                Color(), &identity));

    rootSky.reset(new SceneNode(
                NullActorID, "SkyGroup", RenderPass::Sky,
                Color(), &identity));

    rootInvisible.reset(new SceneNode(
                NullActorID, "InvisibleGroup", RenderPass::NotRendered,
                Color(), &identity));
}

RootNode::~RootNode()
{
    // TODO
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
            assert("Hmm, maybe we should implement this " && child->getRenderPass());
    }
    return true;
}

}
