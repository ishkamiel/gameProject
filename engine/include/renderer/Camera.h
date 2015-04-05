#ifndef CAMERA_H_
#define CAMERA_H_

#include "renderer/SceneNode.h"

#include <memory>

namespace pdEngine
{

class Camera : public SceneNode
{
public:
    //Camera() {};
    virtual ~Camera () {};
};

using Camera_sprt = std::shared_ptr<Camera>;

}
#endif /* CAMERA_H_ */
