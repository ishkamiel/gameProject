#ifndef ROOTNODE_H_
#define ROOTNODE_H_

#include "renderer/SceneNode.h"
#include "renderer/Scene.h"

namespace pdEngine
{

class RootNode : public SceneNode
{
public:
    RootNode ();
    virtual ~RootNode ();

    virtual bool v_AddChild(SceneNode_sptr child) override;
    virtual bool v_RenderChildren(Scene* scene) override;
    virtual bool v_IsVisible(Scene* scene) const override;

private:

    SceneNode_sptr rootStatic;
    SceneNode_sptr rootActor;
    SceneNode_sptr rootSky;
    SceneNode_sptr rootInvisible;
    
};

}

#endif /* ROOTNODE_H_ */
