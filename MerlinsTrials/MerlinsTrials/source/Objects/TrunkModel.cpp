#include "stdafx.h"
#include "TrunkModel.h"

TrunkModel::TrunkModel(Geometry * in_geometry, ID3D11DeviceContext* in_context) : ModelBase(in_geometry, in_context)
{
	this->collideBox = CollisionBox(this->m_bb);
}

TrunkModel::~TrunkModel()
{
}

CollisionBox TrunkModel::getBoundingBox() const
{
	return this->collideBox;
}
