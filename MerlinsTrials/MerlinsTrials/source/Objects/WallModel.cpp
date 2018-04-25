#include "stdafx.h"
#include "WallModel.h"

WallModel::WallModel(Geometry * in_geometry) : ModelBase(in_geometry)
{
	this->collideBox = CollisionBox(this->m_bb);
}

WallModel::~WallModel()
{
}

CollisionBox WallModel::getBoundingBox() const
{
	return this->collideBox;

}
