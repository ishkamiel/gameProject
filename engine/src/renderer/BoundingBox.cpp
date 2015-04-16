/*
 * BoundingBox.cpp
 *
 *  Created on: Apr 11, 2015
 *      Author: ishkamiel
 */

#include "renderer/BoundingBox.h"

namespace pdEngine
{

BoundingBox::BoundingBox(ActorID id, const std::string& name, RenderPass rp, const Color& c, Matrix4* t)
: SceneNode (id, name, rp, c, t)
{


}

BoundingBox::~BoundingBox()
{}

bool BoundingBox::v_Render(Scene* scene)
{

	return true;
}

bool BoundingBox::v_OnRestore(Scene* scene)
{
	(void)scene;
	return true;
}

bool BoundingBox::v_IsVisible(Scene* scene) const
{
	(void)scene;
	return true;
}

}
