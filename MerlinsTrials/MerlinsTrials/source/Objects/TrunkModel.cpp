#include "stdafx.h"
#include "TrunkModel.h"

TrunkModel::TrunkModel(Geometry * in_geometry) : ModelBase(in_geometry)
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
