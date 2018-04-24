#include "stdafx.h"
#include "WallModel.h"


WallModel::~WallModel()
{
}

void WallModel::setVisibility(const bool &in_var)
{
	this->visible = in_var;
}

void WallModel::setBoundryWall()
{
	this->boundryWall = true;
}


void WallModel::createBoundingBox()
{
	/*XMFLOAT3 *points = new XMFLOAT3[this->geometry->getVertexCount()];
	for (int i = 0; i < this->geometry->getVertexCount(); i++)
	{
		points[i] = this->geometry->vertices.at(i).pos;
	}
	this->collideBox = CollisionBox(points, this->geometry->getVertexCount());*/
	
}

bool WallModel::isVisible() const
{
	return this->visible;
}

bool WallModel::getBoundryWall() const
{
	return this->boundryWall;
}

CollisionBox WallModel::getBoundingBox() const
{
	return this->collideBox;

}

DirectX::XMMATRIX WallModel::getWorldMatrix() const
{
	return this->getWorld();
}
