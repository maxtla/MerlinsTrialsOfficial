#pragma once
#ifndef WALLMODEL_H
#define WALLMODEL_H
#include "ModelBase.h"
#include"..\Collision\CollisionBox.h"


class WallModel : public ModelBase
{
private:
	CollisionBox collideBox; //keeps obb
	

public:
	WallModel(Geometry * in_geometry, ID3D11DeviceContext* in_context);
	WallModel(DirectX::XMMATRIX world, bool isSolid, bool isVisible) : ModelBase(world, isSolid, isVisible){}
	~WallModel();

	void Draw();
	CollisionBox getBoundingBox() const;
};

#endif // !WALLMODEL_H
