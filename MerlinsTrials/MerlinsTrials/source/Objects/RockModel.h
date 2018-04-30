#pragma once
#ifndef ROCKMODEL_H
#define ROCKMODEL_H
#include"..\Objects\ModelBase.h"
#include"..\Collision\CollisionBox.h"

class RockModel : public ModelBase
{
private:
	CollisionBox collideBox;

public:
	RockModel(Geometry* in_geometryVec, ID3D11DeviceContext* in_context);
	RockModel(DirectX::XMMATRIX world, bool isSolid, bool isVisible);
	~RockModel();
};
#endif // !ROCKMODEL_H
