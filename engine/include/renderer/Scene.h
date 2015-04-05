#ifndef SCENE_H_
#define SCENE_H_

#include <glm/fwd.hpp>

#include <memory>

namespace pdEngine {

class Camera;

class Scene
{

public:
    Scene ();
    virtual ~Scene ();

    std::shared_ptr<Camera> getCamera();

    void pushAndSetMatrix(const glm::mat4* toWorld);
    void popMatrix();

protected:

private:
};

using Scene_sptr = std::shared_ptr<Scene>;

}
#endif /* SCENE_H_ */
