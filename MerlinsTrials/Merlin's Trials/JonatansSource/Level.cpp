#include "Level.h"

Level::Level()
{
	this->fileName = ""; //empty init
	this->objImporter = nullptr;
	this->device = nullptr;
}

Level::~Level()
{
	this->objImporter = nullptr;
	this->geometryVec.clear();
	this->fileName.clear();
}

void Level::createModel(const std::string &meshName, const int &n)
{


		if (meshName == "Wall")
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
		else if (meshName == "Rock")
		{
			ModelBase base(this->device, &this->geometryVec[n]);
			base.createBuffers();
			this->miscModels.push_back(base);
		}
	
}

bool Level::collisionCheck()
{



	return false;
}

bool Level::initialize(ID3D11Device* in_device, ObjectImporter * importer, const std::string &in_fileName)
{

	this->device = in_device;
	this->fileName = in_fileName;
	this->objImporter = importer;


}

bool Level::initializeModels()
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
