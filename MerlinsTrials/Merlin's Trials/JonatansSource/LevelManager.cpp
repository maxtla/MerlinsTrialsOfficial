#include "LevelManager.h"

#define PATH_ONE "TestTri.obj"

#define NUM_OF_LEVELS 1

LevelManager::LevelManager()
{
	this->cDimension = Dimension::NORMAL;
	this->cLevel = 0;
}

LevelManager::~LevelManager()
{
	
}

bool LevelManager::initLevelManager(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext, ObjectImporter * in_importer)
{
	bool rValue = false;
	this->device = in_device;
	this->deviceContext = in_deviceContext;
	this->importer = in_importer;

	rValue = this->initiateLevels();

	return rValue;
}

void LevelManager::updateCurrentLevel(float &dt)
{
	//other stuff

	this->levelOne.collisionCheck();

	this->Draw();
}

void LevelManager::changeLevel()
{
	this->cLevel++;
}

bool LevelManager::initiateLevels()
{
	bool rValue = false;

	rValue = this->levelOne.initialize(this->device, this->importer, PATH_ONE);


	return true;
}

void LevelManager::Draw()
{

	//set shaders
	//set cbs
	//set render targets
	//set vbuffers
	//set ibuffers
	//do whatever is needed to draw geometry
	//this->deviceContext->Draw();



	switch (this->cDimension)
	{
	case NORMAL:
		//do D3D11 stuff

		this->deviceContext->IASetVertexBuffers();
		this->deviceContext->IASetIndexBuffer();

		this->deviceContext->VSSetShader();
		this->deviceContext->VSSetConstantBuffers();
	
		this->deviceContext->PSSetShaderResources();
		this->deviceContext->PSSetConstantBuffers();
		this->deviceContext->PSSetShader();
		break;

	case OTHER:
		//do D3D11 stuff
		//transparenta väggar

		this->deviceContext->IASetVertexBuffers();
		this->deviceContext->IASetIndexBuffer();

		this->deviceContext->VSSetShader();
		this->deviceContext->VSSetConstantBuffers();
		
		this->deviceContext->PSSetShaderResources();
		this->deviceContext->PSSetConstantBuffers();
		this->deviceContext->PSSetShader();
		break;
	}

	//Draw();

}

void LevelManager::callSwapDimension()
{
	//swap current dimension use
	switch (cDimension)
	{
	case NORMAL:
	{
		this->cDimension = Dimension::OTHER;
		break;
	}
	case OTHER:
	{
		this->cDimension = Dimension::NORMAL;
		break;
	}
	}

}

void LevelManager::loadNextLevel()
{
	//increment indx to next level
	this->cLevel++;

}

unsigned int LevelManager::getNumOfLevels() const
{
	return NUM_OF_LEVELS;
}
