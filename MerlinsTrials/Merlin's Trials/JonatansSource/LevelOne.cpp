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

	for (int i = 0; i < this->terrainModels.size(); i++)
	{

		//input layout
		//topology
		this->updateMatrices(this->terrainModels[i].getWorld());
		this->rebindCB();

		this->deviceContext->IASetIndexBuffer(this->terrainModels[i].getIBuffer(), DXGI_FORMAT_R32_UINT, 0);
		ID3D11Buffer * vbuffer = this->terrainModels[i].getVBuffer();
		this->deviceContext->IASetVertexBuffers(0, 1, &vbuffer, (UINT*)sizeof(Geometry::Vertex), 0);

		this->deviceContext->DrawIndexed(this->terrainModels[i].getGeometry()->indices.size(), 0 ,0);
	}

	for (int i = 0; i < this->wallModels.size(); i++)
	{
		if (this->wallModels[i].isVisible())
		{
			//input layout
			//topology
			this->updateMatrices(this->terrainModels[i].getWorld());
			this->rebindCB();

			this->deviceContext->IASetIndexBuffer(this->wallModels[i].getIBuffer(), DXGI_FORMAT_R32_UINT, 0);
			ID3D11Buffer * vbuffer = this->wallModels[i].getVBuffer();
			this->deviceContext->IASetVertexBuffers(0, 1, &vbuffer, (UINT*)sizeof(Geometry::Vertex), 0);

			this->deviceContext->DrawIndexed(this->wallModels[i].getGeometry()->indices.size(), 0, 0);
		}
	}

	for (int i = 0; i < this->miscModels.size(); i++)
	{
		//input layout
		//topology
		this->updateMatrices(this->terrainModels[i].getWorld());
		this->rebindCB();

		this->deviceContext->IASetIndexBuffer(this->miscModels[i].getIBuffer(), DXGI_FORMAT_R32_UINT, 0);
		ID3D11Buffer * vbuffer = this->miscModels[i].getVBuffer();
		this->deviceContext->IASetVertexBuffers(0, 1, &vbuffer, (UINT*)sizeof(Geometry::Vertex), 0);

		this->deviceContext->DrawIndexed(this->miscModels[i].getGeometry()->indices.size(), 0 , 0);
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

bool LevelOne::initialize(ID3D11Device* in_device, ObjectImporter * importer, const std::string &in_fileName, Player* player)
{
	this->player = player;
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
