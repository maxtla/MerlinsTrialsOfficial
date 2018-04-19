#include "WallModel.h"

WallModel::WallModel() : ModelBase()
{
}

WallModel::WallModel(const DirectX::XMMATRIX & in_wMatrix, const Geometry * in_geometry) : ModelBase(in_wMatrix, in_geometry)
{

}

WallModel::~WallModel()
{
}

DirectX::BoundingBox WallModel::getBoundingBox() const
{
	return this->bBox;
}
