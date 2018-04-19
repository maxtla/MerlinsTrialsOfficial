#include "ModelBase.h"

ModelBase::ModelBase(const DirectX::XMMATRIX &in_wMatrix, const Geometry* in_Geometry)
{
	this->geometry = in_Geometry;
	this->wMatrix = in_wMatrix;
}

ModelBase::~ModelBase()
{
}

void ModelBase::setGeometry(const Geometry * in_geometry)
{
	this->geometry = in_geometry;
}

const Geometry * ModelBase::getGeometry() const
{
	return this->geometry;
}

