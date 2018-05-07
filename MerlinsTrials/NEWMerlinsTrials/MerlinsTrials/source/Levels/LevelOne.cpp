#include "stdafx.h"
#include "LevelOne.h"


LevelOne::~LevelOne()
{
	delete m_basicShader;
	m_basicShader = nullptr;
	delete m_level;
	m_level = nullptr;
}

void LevelOne::Update()
{
	m_level->Update(m_player);
	pWallManager->Update();

	//update player last
	m_player->update();
}

void LevelOne::Draw()
{
	m_level->Draw(m_player->getCam()->getView(), m_player->getCam()->getProjection());
	m_player->draw();
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


bool LevelOne::initialize(ID3D11Device* in_device, ID3D11DeviceContext* in_deviceContext, Player* player)
{
	//we can actually have an temporary instance of this in each level/manager since it is basically just a function class. aka it takes like no space
	ObjectImporter m_importer; 
	//set the player ptr
	m_player = player;
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
	
	//free the vector (only the pointers) --- the level class destructor will delete the Mesh instances
	
	//-----INITIALIZE MANAGERS-----
	pWallManager = new WallManager();
	if (!pWallManager->initialize(levelMesh, in_deviceContext, in_device))
		return false;
	pWallManager->setPlayer(player);



	levelMesh.clear();
	m_timer.startTimer();
	return true;
}
