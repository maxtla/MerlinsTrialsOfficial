#include "stdafx.h"
#include"WandModel.h"


WandModel::WandModel(DirectX::XMMATRIX world) : ModelBase(world, true, true) {

	this->wMatrix = world;
	this->standardMatrix = world;
	this->pos = {0.0f, 0.0f, 0.0f};
	this->animationMatrix = XMMatrixIdentity();
	this->inPickupAnimation = false;
	this->wandGoingUp = true;
}

WandModel::~WandModel() {

	delete this->shader_NormMap;
	for (size_t i = 0; i < m_Meshes.size(); i++)
		delete m_Meshes[i];
	m_Meshes.clear();
	/*delete this->hej;*/
}

///////////////////////////////////MISC//////////////////////////////////////
void WandModel::followPlayer(DirectX::XMMATRIX view) {

	this->wMatrix = this->animationMatrix * this->standardMatrix * DirectX::XMMatrixInverse(&DirectX::XMMatrixDeterminant(view), view);
	//this->wMatrix = Matrix::CreateRotationY(XM_PI * 0.5) * Matrix::CreateRotationZ(XM_PI * 0.5) * Matrix::CreateScale(0.01f) * Matrix::CreateTranslation(0.0f, 0.5f, 0.0f);
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
	this->aniTime.startTimer();
	this->pickupTime.startTimer();
	
	/*hej = new SoundEngine();
	hej->loadSound(".//Assets//Sounds//Trollstav3.wav");
	hej->setSoundVolume(50);*/
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

	this->animation();

	if (this->inPickupAnimation == true)
	{		
		this->pickupAnimation();
	}	
	
	//Wand moves with player
	this->followPlayer(view);
}

void WandModel::animation()
{
	float newPosY = cosf(this->aniTime.frameDiff()*0.002);
	float newPosZ = 0;
	float newPosX = 0;
	Matrix rotation;
	if(GetAsyncKeyState(KEY::W) && !GetAsyncKeyState(KEY::S))
	{
		newPosY = cosf(this->aniTime.frameDiff() * 0.01);
		rotation = rotation.CreateRotationX(DEGTORAD(-20));
	}
	if (GetAsyncKeyState(KEY::S) && !GetAsyncKeyState(KEY::W))
	{
		newPosY = cosf(this->aniTime.frameDiff()*0.01);
		rotation = rotation.CreateRotationX(DEGTORAD(20));
	}
	if ((GetAsyncKeyState(KEY::A) || GetAsyncKeyState(KEY::D)) && !(GetAsyncKeyState(KEY::A) && GetAsyncKeyState(KEY::D)))
	{
		newPosX = cosf(this->aniTime.frameDiff()*0.01);
	}
	

	this->animationMatrix = Matrix(this->animationMatrix).CreateTranslation(Vector3(newPosX,newPosY,newPosZ)) + rotation;
	if (newPosY >= -0.05+1 && newPosY < 0.05+1 && this->aniTime.frameDiff() > 500)
	{
		this->aniTime.reset();
	}
}

void WandModel::pickupAnimation()
{
	float newPosY = 0;
	float newPosZ = 0;
	float newPosX = 0;	 
	Matrix rotation;	

	if (this->pickupTime.frameDiff() < 200 && this->wandGoingUp == true)
	{
		//newPosY = this->pickupTime.frameDiff()*0.01;
		rotation = rotation.CreateRotationY(DEGTORAD(55)) * this->pickupTime.frameDiff()/100;
		this->animationMatrix = Matrix(this->animationMatrix).CreateTranslation(Vector3(newPosX, newPosY, newPosZ)) + rotation;
	}
	else if (this->pickupTime.frameDiff() >= 200 && wandGoingUp == true)
	{
		this->wandGoingUp = false;
		this->pickupTime.reset();
		
		/*hej->playSound();*/
	}
	
	if(wandGoingUp == false && this->pickupTime.frameDiff() < 200)
	{
		//newPosY = this->pickupTime.frameDiff() * -0.01;
		rotation = rotation.CreateRotationY(DEGTORAD(-55)) * this->pickupTime.frameDiff()/100;
		this->animationMatrix = Matrix(this->animationMatrix).CreateTranslation(Vector3(newPosX, newPosY, newPosZ)) + rotation;
	}
	else if (wandGoingUp == false && this->pickupTime.frameDiff() >= 200)
	{
		this->inPickupAnimation = false;
		this->wandGoingUp = true;
	}	
}

void WandModel::resetPickupTimer()
{
	this->pickupTime.reset();
}

void WandModel::createMatrix(Vector3 pos) {

	//Init matrix
	this->pos.x = (pos.x - 6.495f);
	this->pos.y = (pos.y - 0.505f);
	this->pos.z = (pos.z + 0.015f);

	this->standardMatrix = DirectX::XMMatrixRotationZ(2.5) *
		XMMatrixRotationX(DEGTORAD(180 - 33)) *
		DirectX::XMMatrixRotationY(0.20) *
		DirectX::XMMatrixScaling(0.0005f, 0.0005f, 0.001f) *
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

void WandModel::setInPickupAnimation(bool value)
{
	this->inPickupAnimation = value;
}
