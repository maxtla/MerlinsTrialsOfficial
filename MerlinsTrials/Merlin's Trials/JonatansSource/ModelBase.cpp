#include "ModelBase.h"

ModelBase::ModelBase()
{

}

ModelBase::ModelBase()
{
}

ModelBase::~ModelBase()
{
}

void ModelBase::setGeometry(const Geometry * in_geometry)
{
	this->geometry = in_geometry;
}

void ModelBase::setBoundingType(const BBType &in_type)
{
	this->boundBType = in_type;
}

const Geometry * ModelBase::getGeometry()
{
	return this->geometry;
}

unsigned int ModelBase::getBoundingBoxType()
{
	return this->boundBType;
}
