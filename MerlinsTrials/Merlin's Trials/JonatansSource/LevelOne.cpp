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

void LevelOne::createCB()
{

	HRESULT hr;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(Matrices);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &this->matrices;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	hr = this->device->CreateBuffer(&cbDesc, &InitData, &this->constBuffer);
	if (FAILED(hr))
	{
		//höhöhö
		exit(-1);
	}
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
			wall.setBoundryWall();
			this->boundryWalls.push_back(wall);

		}
		else if (meshName == "Terrain")
		{
			TerrainModel terr(this->device, &this->geometryVec[n]);
			terr.createBuffers();
			this->terrainModels.push_back(terr);
		}
		//else if (meshName == "Water")
		//{
		//	//do water stuff
		//	.createBuffers();
		//	this->terrainModels.push_back(terr);
		//}
		else
		{
			ModelBase base(this->device, &this->geometryVec[n]);
			base.createBuffers();
			this->miscModels.push_back(base);
		}
}

void LevelOne::updateMatrices(const DirectX::XMMATRIX &in_matrix)
{
	this->matrices.projection = this->player.getCamera().getProjection();
	this->matrices.view = this->player.getCamera().getView();
	this->matrices.world = in_matrix;
}

void LevelOne::rebindCB()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	this->deviceContext->Map(this->constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, &this->matrices, sizeof(this->matrices));
	this->deviceContext->Unmap(this->constBuffer, 0);
}

void LevelOne::Draw()
{
	switch (this->cDimension)
	{
	case Dimension::NORMAL:
		this->normalWallManager.Draw();
		break;
	case Dimension::OTHER:
		this->otherWallManager.Draw();
		break;
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

bool LevelOne::initialize(ID3D11Device* in_device, ID3D11DeviceContext* in_deviceContext, ObjectImporter * importer, const std::string &in_fileName, Player* player)
{
	this->player = player;
	this->device = in_device;
	this->deviceContext = in_deviceContext;
	this->fileName = in_fileName;
	this->objImporter = importer;

	this->initializeModels();
	this->normalWallManager.initialize(in_device, in_deviceContext);
	this->otherWallManager.initialize(in_device, in_deviceContext);
	this->terrainManager.initialize(in_device, in_deviceContext);
	this->miscManager.initialize(in_device, in_deviceContext);
	//this->waterManager.initialize(in_device, in_deviceContext);


	this->normalWallManager.setModelPtr(&this->wallModels, &this->boundryWalls);
	this->otherWallManager.setModelPtr(nullptr, &this->boundryWalls);
	this->terrainManager.setModelPtr(&this->terrainModels);
	this->miscManager.setModelPtr(&this->miscModels);

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
		else
		{
			meshName = meshName.substr(0, pos - 1);

			//create model and bb with current geometry
			this->createModel(meshName, n);
		}

	}

	return rValue;

}

void LevelOne::setDimension(const Dimension &in_dimension)
{
	this->cDimension = in_dimension;
}

Dimension LevelOne::getCurrentDimension() const
{
	return this->cDimension;
}
