#pragma once
#ifndef WALLMODEL_H
#define WALLMODEL_H
#include "ModelBase.h"
#include"CollisionBox.h"


class WallModel : public ModelBase
{
private:
	CollisionBox collideBox; //keeps obb
	

public:
	WallModel(Geometry * in_geometry);
	WallModel(DirectX::XMMATRIX world, bool isSolid, bool isVisible) : ModelBase(world, isSolid, isVisible){}
	~WallModel();

	CollisionBox getBoundingBox() const;
};

#endif // !WALLMODEL_H
