#include "stdafx.h"
#include "ModelBase.h"

ModelBase::ModelBase(Geometry * in_geometry)
{
	this->pGeometry = in_geometry;
	this->wMatrix = DirectX::XMMatrixIdentity();
}

ModelBase::~ModelBase()
{

}

void ModelBase::setWorldMatrix(const DirectX::XMMATRIX & in_wMatrix)
{
	this->wMatrix = in_wMatrix;
}

void ModelBase::createBoundingOrientBox()
{
	std::vector<DirectX::XMFLOAT3> vec;
	DirectX::XMFLOAT3 fVec;
	DirectX::XMVECTOR xVec;

	for (auto var : this->pGeometry->vertices)
	{
		//transform to worldspace
		xVec = DirectX::XMVector3Transform(var.pos, this->wMatrix);
		DirectX::XMStoreFloat3(&fVec, xVec);
		vec.push_back(fVec);
	}

	//create obb in worldspace
	DirectX::BoundingOrientedBox::CreateFromPoints(this->m_bb, vec.size(), vec.data(), sizeof(DirectX::XMFLOAT3));
}

DirectX::XMMATRIX ModelBase::getWorld() const
{
	return this->wMatrix;
}

