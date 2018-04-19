#include "TerrainModel.h"

TerrainModel::TerrainModel()
{
}

TerrainModel::TerrainModel(ID3D11Device * in_device) : ModelBase(in_device)
{
}

TerrainModel::TerrainModel(ID3D11Device * in_device, const Geometry * in_geometry) : ModelBase(in_device, in_geometry)
{
}

TerrainModel::~TerrainModel()
{
}
