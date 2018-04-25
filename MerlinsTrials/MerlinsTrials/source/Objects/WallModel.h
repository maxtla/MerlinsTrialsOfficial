#pragma once
#ifndef WALLMODEL_H
#define WALLMODEL_H
#include "ModelBase.h"
#include "..\Collision\CollisionBox.h"


class WallModel : public ModelBase
{
private:
	CollisionBox collideBox; //keeps obb
	bool boundryWall = false;
	bool visible = true;

public:
	WallModel(DirectX::XMMATRIX world) : ModelBase(world, true, true){}
	~WallModel();

	void setVisibility(const bool &in_var);
	void setBoundryWall();
	void createBoundingBox();

	bool isVisible() const;
	bool getBoundryWall() const;
	CollisionBox getBoundingBox() const;
	DirectX::XMMATRIX getWorldMatrix() const;

};

#endif // !WALLMODEL_H
