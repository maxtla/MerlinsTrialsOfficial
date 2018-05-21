#pragma once
#ifndef CUBEMANAGER_H
#define CUBEMANAGER_H
#include"..\Shaders\BasicShader.h"
#include"..\Shaders\NormalMapShader.h"
#include"..\Player\Player.h"
#include"..\Objects\PedestalModel.h"
#include"..\Objects\CubeModel.h"
#include"..\Levels\LevelState.h"
#include"..\Helpers\Timer.h"



class CubeManager
{
private:
	ID3D11DeviceContext * context;
	ID3D11Device * device;
	BasicShader * m_BasicShader;
	NormalMapShader * m_NormalMapShader;

	//levelOne
	std::vector<CubeModel*> m_ForestCubes;
	std::vector<CubeModel*> m_LabyrinthCubes;
	std::vector<PedestalModel*> m_ForestPedestals;
	std::vector<PedestalModel*> m_LabyrinthPedestals;

	Player * pPlayer;
	ObjectImporter importer;
	LevelState* state;		
	SoundEngine* putDownSound;
	int eraseId;
	bool cubeIsAboutToBeErased;
	Timer eraseDelay;

	XMMATRIX redCubeForest = DirectX::SimpleMath::Matrix::CreateTranslation(5.15f, 0.3f, -7.0f);
	XMMATRIX greenCubeForest = DirectX::SimpleMath::Matrix::CreateTranslation(1.20f, 0.3f, 2.45f);
	XMMATRIX blueCubeForest = DirectX::SimpleMath::Matrix::CreateTranslation(-9.0f, 0.5f, -7.88f);
	XMMATRIX yellowCubForest = DirectX::SimpleMath::Matrix::CreateTranslation(5.67f, 0.2f, 5.4f);

	XMMATRIX redCubeLaby = DirectX::SimpleMath::Matrix::CreateTranslation(-8.4f, 0.3f, -0.15f);
	XMMATRIX greenCubeLaby = DirectX::SimpleMath::Matrix::CreateTranslation(-8.4f, 0.3f, .15f);
	XMMATRIX blueCubeLaby = DirectX::SimpleMath::Matrix::CreateTranslation(-8.7f, 0.3f, .15f);
	XMMATRIX yellowCubLaby = DirectX::SimpleMath::Matrix::CreateTranslation(-8.7f, 0.3f, -0.15f);


	void checkCubesOnPedistal(); //triggers state
	int checkCollision();
	bool checkPickUp();
	void resetLabyCubesPos();
	void eraseCube();
public:
	CubeManager();
	~CubeManager();
	bool initialize(ID3D11DeviceContext * pDevCon, ID3D11Device* pDev, Player* in_player, LevelState* in_state);
	void initializeLevelOne();
	void initializeLevelTwo();
	void swapDimension();
	void SwapPhases();
	void update();
	void Draw(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View);
	void reset();

};
#endif // !CUBEMANAGER_H
