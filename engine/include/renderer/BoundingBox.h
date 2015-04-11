/*
 * BoundingBox.h
 *
 *  Created on: Apr 11, 2015
 *      Author: ishkamiel
 */

#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include "renderer/SceneNode.h"

namespace pdEngine
{

class BoundingBox : public SceneNode
{
	BoundingBox() = delete;
	BoundingBox(ActorID id, const std::string& name, RenderPass rp, const Color& c, Matrix4* t);
	virtual ~BoundingBox();

    virtual bool v_Render(Scene*) override;
    virtual bool v_OnRestore(Scene*) override;
    virtual bool v_IsVisible(Scene*) const override;

};


}
#endif /* BOUNDINGBOX_H_ */
