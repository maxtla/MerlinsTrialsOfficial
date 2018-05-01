#include "stdafx.h"
#include "Level.h"

Level::Level()
{
	this->fileName = "Obj//Level1.obj";
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

	//Create buffers
	for (size_t i = 0; i < this->objects.size(); i++) {
		
		this->objects[i].createBuffers(in_device);

	}

	return rValue;
}

std::vector<Mesh>* Level::getGeometry()
{
	return &this->objects;
}

int Level::findObject(std::string name) {

	for (int i = 0; i < this->objects.size(); i++) {



	}
	return 0;
}