#include "BoxModel.h"


BoxModel::BoxModel(const BBType &in_BoundingType, const DirectX::XMMATRIX &in_wMatrix, const Geometry * in_Geometry)
{
	this->boundBType = in_BoundingType;
	this->wMatrix = in_wMatrix;
	this->geometry = in_Geometry;
}

BoxModel::~BoxModel()
{
}

void BoxModel::setBoundingBox()
{
	//create boundingBox
	DirectX::XMFLOAT3 centre;
	DirectX::XMFLOAT3 extents(1, 1, 1);
	this->bBox = DirectX::BoundingBox(centre, extents);

}

DirectX::BoundingBox BoxModel::getBoundingBox()
{
	return this->bBox;
}
