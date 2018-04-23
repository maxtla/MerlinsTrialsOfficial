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
	this->geometry->vertices;
}

DirectX::BoundingBox WallModel::getBoundingBox() const
{
	return this->OBBox;
}
