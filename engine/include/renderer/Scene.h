#ifndef SCENE_H_
#define SCENE_H_

#include <memory>

namespace pdEngine {

class Scene
{
public:
    Scene ();
    virtual ~Scene ();

protected:

private:
};

using Scene_sptr = std::shared_ptr<Scene>;

}
#endif /* SCENE_H_ */
