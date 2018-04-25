#include "stdafx.h"
#include "TrunkModel.h"

TrunkModel::TrunkModel(Geometry * in_var) : ModelBase(in_var)
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
