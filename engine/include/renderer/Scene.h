#ifndef SCENE_H_
#define SCENE_H_

#include "Actor.h"
#include "Timer.h"
#include "renderer/I_Renderer.h"
#include "renderer/I_SceneNode.h"
#include "renderer/SceneNode.h"

#include <glm/fwd.hpp>

#include <map>
#include <memory>
#include <stack>

namespace pdEngine {

class CameraNode;
class SKyNode;
class LgithNode;
class LightManager;
using CameraNode_sptr = std::shared_ptr<CameraNode>;
using LightManager_sptr = std::shared_ptr<LightManager>;

class Scene
{

public:
    Scene ();
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

    void pushAndSetMatrix(const glm::mat4* toWorld);
    void popMatrix(void);
    const glm::mat4* getTopMatrix(void);

    LightManager_sptr getLightManager();

protected:

private:

protected:
	std::shared_ptr<CameraNode> m_Camera;
    std::shared_ptr<I_Renderer> m_Renderer;
    std::shared_ptr<SceneNode> m_Root;

    std::stack<glm::mat4> m_TranlsationMatrices;
    /* Alpha? */

    std::map<ActorID, SceneNode_sptr> m_ActorMap;

    LightManager_sptr m_LightManager;

};

using Scene_sptr = std::shared_ptr<Scene>;

}

#endif /* SCENE_H_ */
