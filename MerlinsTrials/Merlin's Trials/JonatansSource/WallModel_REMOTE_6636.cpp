#include "WallModel.h"

WallModel::WallModel() : ModelBase()
{
}

WallModel::WallModel(ID3D11Device * in_device, const Geometry* in_geometry) : ModelBase(in_device, in_geometry)
{
}

WallModel::WallModel(ID3D11Device *in_device, const DirectX::XMMATRIX & in_wMatrix, const Geometry * in_geometry) : ModelBase(in_device, in_wMatrix, in_geometry)
{

}

WallModel::~WallModel()
{
}

void WallModel::createBoundingBox()
{
	XMFLOAT3 *points = new XMFLOAT3[this->geometry->getVertexCount()];
	for (int i = 0; i < this->geometry->getVertexCount(); i++)
	{
		points[i] = this->geometry->vertices.at(i).pos;
	}
	this->collideBox = CollisionBox(points, this->geometry->getVertexCount());
	
}

CollisionBox WallModel::getBoundingBox() const
{
	return this->collideBox;
}
