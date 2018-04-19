#include "Level.h"

Level::Level()
{
	this->fileName = ""; //empty init
	this->objImporter = nullptr;
}

Level::~Level()
{
	this->objImporter = nullptr;
	this->geometryVec.clear();
	this->fileName.clear();
}

void Level::createModels()
{
	unsigned int walls, terrains, Rock;

	for (UINT32 i = 0; i < meshNames.size(); i++)
	{
		if (this->meshNames[i] == "Wall")
		{

		}
		else if (this->meshNames[i] == "Terrain")
		{

		}
		else if (this->meshNames[i] == "Rock")
		{

		}
	}
}

bool Level::initialize(ID3D11Device* in_device, ObjectImporter * importer, const std::string &in_fileName){



	bool rValue = false;
	this->fileName = in_fileName;
	this->objImporter = importer;

	//Load meshes
	rValue = this->objImporter->importModel(this->fileName, this->geometryVec);

	//seperate mesh names
	std::string meshName;
	for (int n = 0; n < this->geometryVec.size(); n++)
	{
		meshName = this->geometryVec[n].getName();
		
		auto pos = meshName.find('_');
		if (pos == std::string::npos)
		{
			return false;
		}
		
		meshName = meshName.substr(0, pos - 1);

		this->meshNames.push_back(meshName);
	}



	//Create buffers
	for (int i = 0; i < this->geometryVec.size(); i++) {
		
		this->geometryVec.at(i).createBuffers(in_device);
	}



	return rValue;
}

std::vector<Geometry>* Level::getGeometryVec()
{
	return &this->geometryVec;
}
