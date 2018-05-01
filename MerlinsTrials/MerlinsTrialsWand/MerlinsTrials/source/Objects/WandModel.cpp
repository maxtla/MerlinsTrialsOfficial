#include "stdafx.h"
#include"WandModel.h"

WandModel::WandModel(DirectX::XMMATRIX world) : ModelBase(world, true, true) {

	this->wMatrix = world;
	this->standardMatrix = world;
	this->wMatrix *= DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f);
	this->pos = {0.0f, 0.0f, 0.0f};

	this->nrOfMeshes = 2;

}

WandModel::~WandModel() {

	//delete this->shader_Basic;
	delete this->shader_NormMap;

}

///////////////////////////////////MISC//////////////////////////////////////
void WandModel::followPlayer(DirectX::XMMATRIX view) {

	this->wMatrix = this->standardMatrix * DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(view), view);

}

void WandModel::init(std::vector<Mesh*> meshes, ID3D11Device* device, ID3D11DeviceContext* deviceC) {

	//Store D3D11 stuff
	this->dev = device;
	this->devC = deviceC;

	//Set meshes and create buffers
	this->setMeshes(meshes);
	for (int i = 0; i < this->m_Meshes.size(); i++) {

		this->m_Meshes.at(i)->createBuffers(device);

	}

	//Create shaders
	//this->shader_Basic = new BasicShader();
	//this->shader_Basic->init(dev, devC);
	//this->shader_Basic->createShader(VertexPosNorm);

	this->shader_NormMap = new NormalMapShader();
	this->shader_NormMap->init(dev, devC);
	this->shader_NormMap->createShader(NO_COLOR);

}

void WandModel::draw(DirectX::XMMATRIX proj, DirectX::XMMATRIX view) {

	//Setup basic shader
	//this->shader_Basic->setBlendState(); //default
	//this->shader_Basic->setDepthStencilState(); //default
	//this->shader_Basic->setRasterizerState(); //default
	//this->shader_Basic->setSamplerState(); //default

	//Setup normalMapShader
	this->shader_NormMap->setBlendState(); //default
	this->shader_NormMap->setDepthStencilState(); //default
	this->shader_NormMap->setRasterizerState(); //default
	this->shader_NormMap->setSamplerState(); //default

	this->devC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Set matrices
	this->shader_NormMap->m_effect->SetMatrices(this->wMatrix, view, proj);

	for (int i = 0; i < this->nrOfMeshes; i++){

		this->m_Meshes[i]->Draw(this->shader_NormMap);

	}

}

void WandModel::update(DirectX::XMMATRIX view) {

	//Wand moves with player
	this->followPlayer(view);

}

void WandModel::createMatrix(Vector3 pos) {

	//Init matrix
	this->standardMatrix = DirectX::XMMatrixRotationZ(90) *
		DirectX::XMMatrixRotationY(30) *
		DirectX::XMMatrixRotationY(25) *
		DirectX::XMMatrixScaling(0.2f, 0.2f, 0.2f) *
		DirectX::XMMatrixTranslation(pos.x, pos.y, (pos.z));

}

///////////////////////////////////GET///////////////////////////////////////
Vector3 WandModel::getPos(void) const{

	return this->pos;

}

int WandModel::getNrOfMeshes(void) const{

	return this->nrOfMeshes;

}

////////////////////////////////////SET///////////////////////////////////////
void WandModel::setPos(Vector3 pos) {

	this->pos = pos;
	this->wMatrix *= DirectX::XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);

}