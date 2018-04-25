#include"ModelBase.h"
#ifndef TERRAINMODEL_H
#define TERRAINMODEL_H

class ModelBase;
class TerrainModel : public ModelBase
{
private:
	
public:
	TerrainModel(Geometry * in_geometry);
	TerrainModel(DirectX::XMMATRIX world) : ModelBase(world) {}
	~TerrainModel();
};


#endif // !TERRAINMODEL_H
