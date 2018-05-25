#include "stdafx.h"
#include "LevelOne.h"


LevelOne::~LevelOne()
{
	delete m_basicShader;
	m_basicShader = nullptr;
	delete m_level;
	m_level = nullptr;
	delete m_Gate;
	m_Gate = nullptr;
	delete m_gateSound;
}

void LevelOne::Update()
{
		switch (this->state->getPhase())
		{
		case PUZZLE_PHASE::FIRST:
		{

			if (this->state->checkCubeStatus())
			{
				if (!this->m_Gate->getIsOpen() && !this->m_Gate->getIsInAnimation())
				{
					this->m_gateSound->playSound();
				}
				this->pCubemanager->SwapPhases();
				this->pCubemanager->swapDimension();

			}

		}
		break;
		case PUZZLE_PHASE::SECOND:
		{
			if (this->state->checkCubeStatus())
			{
				this->state->setIsEndScreen(true);
				this->loadingScreen->startFade(true); //end screen
				this->state->changeLevel();
			}
		}
		break;

		}
		if (this->m_Gate->getIsOpen())
		{
			if (!this->m_levelTimer->getIsActive() && this->state->getTimer() == TIMER::INACTIVE)
			{
				if (this->m_player->getCam()->getCamPos().x <= -9.6f)
				{
					this->state->setTimer(TIMER::START);
					this->m_levelTimer->setTimer(true);
				}
			}
			if (this->state->getTimer() == TIMER::STOP)
			{
				this->m_player->resetPlayer(PLAYER_SPAWN_POINT_LVL1);
				this->pCubemanager->reset();
				this->state->setFCubes(0);
				this->state->setTimer(TIMER::INACTIVE);
				this->state->setDimension(Dimension::NORMAL);
			}
		}



		m_levelTimer->update();
		m_level->Update(m_player);
		pWallManager->Update();
		m_Gate->Update();
		this->pCubemanager->update();
		//update player last
		m_player->update();

		if (m_level->collisionTest(m_player->getAvatar()))
		{
			m_player->resetToLastFramePos();
		}

		if (GetAsyncKeyState(KEY::Return))
		{
			this->loadingScreen->startFade(false);
			this->state->setIsEndScreen(true);
		}

		this->loadingScreen->update();
		this->resetLevel = this->loadingScreen->FadeFinished();
}


void LevelOne::Draw()
{
	if (GetAsyncKeyState(KEY::F))
	{
		m_level->checkFrustrum(m_player->getCam()->getFrustum());
	}
	m_level->Draw(m_player->getCam()->getView(), m_player->getCam()->getProjection());
	m_Gate->Draw(m_player->getCam()->getView(), m_player->getCam()->getProjection());
	this->pCubemanager->Draw(m_player->getCam()->getProjection(), m_player->getCam()->getView());
	m_player->draw();
	this->loadingScreen->Draw();
	this->m_levelTimer->Draw();

#ifndef NDEBUG
	DebugInformation2D::cameraPosToScreen(pD2D, m_player->getCam()->getCamPos());
	DebugInformation2D::FPStoScreen(pD2D, lastFPSCount);
	if (m_timer.frameDiff() >= 1000.0)
	{
		lastFPSCount = frameCounter;
		frameCounter = 0;
		m_timer.reset();
	}
	frameCounter++;
#endif


}

void LevelOne::resetPlayer()
{
	this->m_player->getCam()->setCameraPosition(PLAYER_SPAWN_POINT_LVL1);
}

bool LevelOne::initialize(ID3D11Device* in_device, ID3D11DeviceContext* in_deviceContext, Player* player)
{
	//we can actually have an temporary instance of this in each level/manager since it is basically just a function class. aka it takes like no space
	ObjectImporter m_importer; 
	
	//Init sound class
	this->m_gateSound = new SoundEngine();
	this->m_gateSound->loadSound(GATE_SOUND_PATH);
	this->m_gateSound->setSoundVolume(25);

	//set the player ptr
	m_player = player;
	player->getCam()->setCameraPosition(PLAYER_SPAWN_POINT_LVL1);

	//create a Basic color shader for the level and most other models
	m_basicShader = new BasicShader();
	m_basicShader->init(in_device, in_deviceContext);
	m_basicShader->createShader(VertexPosNormCol);
	//load in the level1 mesh
	std::vector<Mesh*> levelMesh;
	int tryCount = 0;
RetryPoint:
	if (!m_importer.importLevel(LEVEL_ONE, levelMesh, in_device, in_deviceContext) && tryCount < 5)
	{
		//flush the vector and reset it
		for (size_t i = 0; i < levelMesh.size(); i++)
			delete levelMesh[i];
		levelMesh.clear();
		tryCount++;
		goto RetryPoint;
	}
	if (tryCount == 4)
		return false; //after 5 failed attempts return false

	//create our level and set the static mesh
	m_level = new Level();
	m_level->initialize(levelMesh, m_basicShader);
	
	this->state = new LevelState();
	this->state->setIsEndScreen(true);

	this->loadingScreen = new LoadingScreen(in_device, in_deviceContext, player, this->state);
	this->loadingScreen->init();
	this->loadingScreen->setFullStrength();
	this->m_levelTimer = new LevelTimer(in_device, in_deviceContext, this->state);

	this->pCubemanager = new CubeManager();
	this->pCubemanager->initialize(in_deviceContext, in_device, this->m_player, this->state);
	this->pCubemanager->initializeLevelOne();
	this->pCubemanager->SwapPhases();
	this->pCubemanager->swapDimension();



	//free the vector (only the pointers) --- the level class destructor will delete the Mesh instances
	
	//-----INITIALIZE MANAGERS-----
	pWallManager = new WallManager();
	if (!pWallManager->initialize(levelMesh, in_deviceContext, in_device))
		return false;
	pWallManager->setPlayer(player);

	m_Gate = new GateModel(m_basicShader, this->state);
	if (!m_Gate->loadModel(in_device, in_deviceContext))
		return false;

	levelMesh.clear();
	m_timer.startTimer();
	return true;
}

bool LevelOne::ResetLevel()
{
	return this->resetLevel;
}
