#pragma once
#ifndef _MESH_MANAGER_H
#define _MESH_MANAGER_H

#include "..\Helpers\AssetsPaths.h"
#include "..\Importer\Mesh.h"
#include "..\Importer\ObjectImporter.h"
#include <vector>

class MeshManager
{
public:
	MeshManager();
	~MeshManager();
	void initialize(ID3D11Device * pDev, ID3D11DeviceContext * pDevCon);
	bool loadAllGeometry();

	//MASSA GET
	std::vector<std::vector<Mesh*>> getWalls() const { return this->m_Walls; }
	std::vector<std::vector<Mesh*>> getStaticLevels() const { return this->m_StaticLevels; }
	std::vector<Mesh*> getWand() const { return this->m_Wand; }

private:
	ObjectImporter * pObjectImporter = nullptr;
	ID3D11Device * pDev;
	ID3D11DeviceContext * pDevCon;
	//store geometry pointers and associate models with its type
	std::vector<std::vector<Mesh*>> m_Walls;
	std::vector<Mesh*> m_Wand;
	std::vector<std::vector<Mesh*>> m_StaticLevels;


	//load functions
	bool loadWalls();
	bool loadWand();
	bool loadStaticLevels();
};

#endif // !_GEOMETRY_MANAGER_H
