#include "stdafx.h"
#include "WallModel.h"

WallModel::WallModel(Geometry * in_geometry, ID3D11DeviceContext* in_context) : ModelBase(in_geometry, in_context)
{
	this->collideBox = CollisionBox(this->m_bb);
}

WallModel::~WallModel()
{
}

void WallModel::Draw()
{
	this->pGeometry->Draw();
}

CollisionBox WallModel::getBoundingBox() const
{
	return this->collideBox;

}
