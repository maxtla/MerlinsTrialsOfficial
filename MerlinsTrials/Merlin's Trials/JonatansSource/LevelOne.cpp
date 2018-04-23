#include "LevelOne.h"

LevelOne::LevelOne()
{
	this->fileName = ""; //empty init
	this->objImporter = nullptr;
	this->device = nullptr;
}

LevelOne::~LevelOne()
{
	this->objImporter = nullptr;
	this->geometryVec.clear();
	this->fileName.clear();
}

void LevelOne::createModel(const std::string &meshName, const int &n)
{


		if (meshName == "Wall" || meshName == "Trunk")
		{
			WallModel wall(this->device, &this->geometryVec[n]);
			wall.createBoundingBox();
			wall.createBuffers();
			this->wallModels.push_back(wall);
			
		}
		if (meshName == "WallO")
		{
			WallModel wall(this->device, &this->geometryVec[n]);
			wall.createBoundingBox();
			wall.createBuffers();
			this->wallModels.push_back(wall);

		}
		else if (meshName == "Terrain")
		{
			TerrainModel terr(this->device, &this->geometryVec[n]);
			terr.createBuffers();
			this->terrainModels.push_back(terr);
		}
		else
		{
			ModelBase base(this->device, &this->geometryVec[n]);
			base.createBuffers();
			this->miscModels.push_back(base);
		}
	
}

void LevelOne::collisionCheck()
{
	//check 
	if (1)
	{
		//handle

	}

	
}

bool LevelOne::initialize(ID3D11Device* in_device, ObjectImporter * importer, const std::string &in_fileName)
{

	this->device = in_device;
	this->fileName = in_fileName;
	this->objImporter = importer;


}

bool LevelOne::initializeModels()
{
	//Load meshes
	bool rValue = false;
	rValue = this->objImporter->importModel(this->fileName, this->geometryVec);

	//seperate mesh names
	std::string meshName;
	for (int n = 0; n < this->geometryVec.size(); n++)
	{
		meshName = this->geometryVec[n].getName();

		auto pos = meshName.find('_');
		if (pos == std::string::npos)
		{
			OutputDebugString((LPCSTR)"failed to load model name");
			rValue = false;
			break;
		}
		meshName = meshName.substr(0, pos - 1);

		//create model and bb with current geometry
		this->createModel(meshName, n);
	}

	return rValue;

}
