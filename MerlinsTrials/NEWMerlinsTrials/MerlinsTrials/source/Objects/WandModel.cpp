#include "stdafx.h"
#include"WandModel.h"

WandModel::WandModel(DirectX::XMMATRIX world) : ModelBase(world, true, true) {

	this->wMatrix = world;
	this->standardMatrix = world;
	this->pos = {0.0f, 0.0f, 0.0f};
}

WandModel::~WandModel() {

	delete this->shader_NormMap;
	for (size_t i = 0; i < m_Meshes.size(); i++)
		delete m_Meshes[i];
	m_Meshes.clear();
}

///////////////////////////////////MISC//////////////////////////////////////
void WandModel::followPlayer(DirectX::XMMATRIX view) {

	//this->wMatrix = this->standardMatrix * DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(view), view);
	this->wMatrix = Matrix::CreateRotationY(XM_PI * 0.5) * Matrix::CreateRotationZ(XM_PI * 0.5) * Matrix::CreateScale(0.01f) * Matrix::CreateTranslation(0.0f, 0.5f, 0.0f);
}

void WandModel::init(std::vector<Mesh*> meshes, BasicShader* basicS, ID3D11Device* device, ID3D11DeviceContext* deviceC) {

	//Store D3D11 stuff
	this->dev = device;
	this->devC = deviceC;

	//Set meshes
	this->setMeshes(meshes);

	//Create shaders
	this->shader_Basic = basicS;

	this->shader_NormMap = new NormalMapShader();
	this->shader_NormMap->init(dev, devC);
	this->shader_NormMap->createShader(NO_COLOR);

}

void WandModel::draw(DirectX::XMMATRIX view, DirectX::XMMATRIX projection) {

	//Setup basic shader
	this->shader_Basic->setBlendState(); //default
	this->shader_Basic->setDepthStencilState(); //default
	this->shader_Basic->setRasterizerState(RASTERIZERSTATES::CULL_NONE_STATE); //default
	this->shader_Basic->setSamplerState(); //default

	//Setup normalMapShader
	//this->shader_NormMap->setBlendState(); //default
	//this->shader_NormMap->setDepthStencilState(); //default
	//this->shader_NormMap->setRasterizerState(); //default
	//this->shader_NormMap->setSamplerState(); //default

	this->devC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Set matrices
	this->shader_Basic->m_effect->SetMatrices(this->wMatrix, view, projection);

	for (size_t i = 0; i < this->m_Meshes.size(); i++){

		this->m_Meshes[i]->Draw(this->shader_Basic);

	}

}

void WandModel::update(DirectX::XMMATRIX view) {

	//Wand moves with player
	this->followPlayer(view);

}

void WandModel::createMatrix(Vector3 pos) {

	//Init matrix
	this->pos.x = (pos.x + 0.02f);
	this->pos.y = (pos.y - 0.52f);
	this->pos.z = (pos.z - 0.05f);

	this->standardMatrix = DirectX::XMMatrixRotationZ(0) *
		XMMatrixRotationX(0) *
		DirectX::XMMatrixRotationY(0) *
		DirectX::XMMatrixScaling(1.f, 1.f, 1.f) *
		DirectX::XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);

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

}