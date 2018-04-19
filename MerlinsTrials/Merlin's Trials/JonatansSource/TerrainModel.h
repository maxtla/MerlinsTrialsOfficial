#ifndef TERRAINMODEL_H
#define TERRAINMODEL_H
#include"ModelBase.h"

class TerrainModel : public ModelBase
{
private:
	
public:
	TerrainModel();
	TerrainModel(ID3D11Device * in_device);
	TerrainModel(ID3D11Device * in_device, const Geometry * in_geometry);
	~TerrainModel();



};


#endif // !TERRAINMODEL_H
