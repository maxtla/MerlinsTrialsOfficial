#include "stdafx.h"
#include "Level.h"

Level::Level(ID3D11Device *& in_device, ObjectImporter *& importer)
{
	this->device = in_device;
	this->objImporter = importer;
	this->fileName = "";
	this->meshes = nullptr;
	this->standardWorld = DirectX::XMMatrixIdentity(); //
}

Level::~Level()
{
}

bool Level::initialize()
{
	bool rValue = false;

	rValue = this->objImporter->importModel(this->fileName, this->meshes);
	if (rValue)
	{
		//hantera object
		this->createObjects();
	}

	return rValue;
}

void Level::createObjects()
{
	for (UINT32 i = 0; i < this->meshes->size(); i++)
	{
		Object nObject((*this->meshes)[i], this->standardWorld, this->device);
		nObject.setCollision(false);
		nObject.setVisibility(false);
		this->sceneObjects.push_back(nObject);
	}

}
