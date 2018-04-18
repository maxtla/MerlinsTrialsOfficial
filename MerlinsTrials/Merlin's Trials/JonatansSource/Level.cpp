#include "Level.h"

Level::Level()
{
	this->fileName = "TestTri.obj";
}

Level::~Level()
{

	this->objImporter = nullptr;
	this->objects.clear();
	this->fileName.clear();

}

bool Level::initialize(ID3D11Device* in_device, ObjectImporter * importer){

	bool rValue = false;

	//Store importer
	this->objImporter = importer;

	//Load meshes
	rValue = this->objImporter->importModel(this->fileName, this->objects);

	//Create buffers
	for (int i = 0; i < this->objects.size(); i++) {
		
		this->objects.at(i).createBuffers(in_device);

	}

	return rValue;
}

std::vector<Object>* Level::getObjects()
{
	return &this->objects;
}
