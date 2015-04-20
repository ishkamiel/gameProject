#pragma once

#include "actors/Actor.h"
#include "Timer.h"
#include "renderer/I_Renderer.h"
#include "math/Matrix4.h"

#include <map>
#include <memory>
#include <stack>

namespace pdEngine {

class I_SceneNode;
class SceneNode;
class CameraNode;
class SKyNode;
class LgithNode;
class LightManager;

using CameraNode_sptr = std::shared_ptr<CameraNode>;
using LightManager_sptr = std::shared_ptr<LightManager>;
using SceneNode_sptr = std::shared_ptr<I_SceneNode>;

class Scene
{


public:
    Scene (I_Renderer*);
    virtual ~Scene ();

    bool onRender(void);
    bool onRestore(void);
    bool onLostDevice(void);
    bool onUpdate(TimeDelta);

    std::shared_ptr<I_SceneNode> findActor(ActorID);

    bool addChild(ActorID, std::shared_ptr<I_SceneNode>);
    bool removeAChild(ActorID); 

    void setCamera(CameraNode_sptr) ;
    const CameraNode_sptr getCamera(void) const;

    void pushMatrix(const Matrix4* toWorld);
    void popMatrix(void);
    const Matrix4* getTopMatrix(void);

    LightManager_sptr getLightManager();

protected:

private:

protected:
	std::shared_ptr<CameraNode> m_Camera;
    std::shared_ptr<SceneNode> m_Root;

    I_Renderer* m_Renderer; // I_Renderer destroys Scene.

    std::stack<Matrix4> m_TranlsationMatrices;
    /* Alpha? */

    std::map<ActorID, SceneNode_sptr> m_ActorMap;

    LightManager_sptr m_LightManager;

};

using Scene_sptr = std::shared_ptr<Scene>;

}

