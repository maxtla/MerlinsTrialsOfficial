#include "stdafx.h"
#include "RockModel.h"

RockModel::RockModel(Geometry * in_geometryVec, ID3D11DeviceContext * in_context) : ModelBase(in_geometryVec, in_context)
{
	this->collideBox = CollisionBox(this->m_bb);
}

RockModel::RockModel(DirectX::XMMATRIX world, bool isSolid, bool isVisible) : ModelBase(world, isSolid, isVisible)
{
}

RockModel::~RockModel()
{
}
