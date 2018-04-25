#include "stdafx.h"
#include "ModelBase.h"



ModelBase::~ModelBase()
{
}

void ModelBase::setWorldMatrix(const DirectX::XMMATRIX & in_wMatrix)
{
	this->wMatrix = in_wMatrix;
}

void ModelBase::createBoundongOrientBox()
{

}


DirectX::XMMATRIX ModelBase::getWorld() const
{
	return this->wMatrix;
}

