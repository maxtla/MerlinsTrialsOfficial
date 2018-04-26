#include "stdafx.h"
#include "ModelBase.h"

ModelBase::ModelBase(Geometry * in_geometry, ID3D11DeviceContext* in_context)
{
	this->context = in_context;
	this->pGeometry = in_geometry;
	this->wMatrix = DirectX::XMMatrixIdentity();
	this->isSolid = true;
	this->isVisible = true;

	this->createBoundingOrientBox();
}

ModelBase::~ModelBase()
{

}

void ModelBase::createBoundingOrientBox()
{
	std::vector<DirectX::XMFLOAT3> vec;
	DirectX::XMFLOAT3 fVec;
	DirectX::XMVECTOR xVec;

	for (auto var : this->pGeometry->vertices_PN)
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

void ModelBase::setGeometry(Geometry * in_adrr)
{
	this->pGeometry = in_adrr;
}

void ModelBase::setBoundingBox(const DirectX::BoundingOrientedBox & in_box)
{
	this->m_bb = in_box;
}

DirectX::BoundingOrientedBox ModelBase::getBoundingBox() const
{
	return this->m_bb;
}

DirectX::SimpleMath::Color ModelBase::getColor() const
{
	return this->m_color;
}

Geometry * ModelBase::getGeometry() const
{
	return this->pGeometry;
}

bool ModelBase::getVisible() const
{
	return this->isVisible;
}

bool ModelBase::getSolid() const
{
	return this->isSolid;
}

void ModelBase::setSolid(const bool & value)
{
	this->isSolid = value;
}

void ModelBase::setVisisble(const bool & value)
{
	this->isVisible = value;
}

void ModelBase::setWorldMatrix(const DirectX::XMMATRIX & in_wMatrix)
{
	this->wMatrix = in_wMatrix;
}