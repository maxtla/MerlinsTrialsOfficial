#include "SphereModel.h"



SphereModel::SphereModel(const BBType &in_boundingType, const DirectX::XMMATRIX &in_wMatrix, const Geometry * in_Geometry)
{
	this->boundBType = in_boundingType;
	this->geometry = in_Geometry;
	this->wMatrix = in_wMatrix;

}

SphereModel::~SphereModel()
{
}

void SphereModel::setBoundingSphere()
{
	//create boundingBox

}

DirectX::BoundingSphere SphereModel::getBoundingSphere()
{
	return this->bSphere;
}
