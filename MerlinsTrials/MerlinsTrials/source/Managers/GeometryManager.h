#pragma once
#ifndef _GEOMETRY_MANAGER_H
#define _GEOMETRY_MANAGER_H

#include "..\Helpers\AssetsPaths.h"
#include "..\Importer\Geometry.h"
#include "..\Importer\ObjectImporter.h"
#include <vector>

class GeometryManager
{
public:
	GeometryManager();
	~GeometryManager();
	void initialize();
	bool loadAllGeometry();
private:
	ObjectImporter * pObjectImporter = nullptr;

	//store geometry pointers and associate models with its type
	std::vector<std::vector<Geometry*>> m_Walls;
	std::vector<std::vector<Geometry*>> m_StaticLevel;


	//load functions
	bool loadWalls();
	bool loadStaticLevel();
};

#endif // !_GEOMETRY_MANAGER_H
