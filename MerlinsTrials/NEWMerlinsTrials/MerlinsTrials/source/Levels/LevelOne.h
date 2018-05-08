#ifndef LEVELONE_H
#define LEVELONE_H

#include "..\Importer\ObjectImporter.h"
#include "..\Helpers\Enumerators.h"
#include "..\Player\Player.h"
#include "..\Shaders\BasicShader.h"
#include "..\Helpers\AssetsPaths.h"
#include "..\Engines\Direct2DEngine.h"
#include "..\Managers\WallManager.h"
#include "..\Managers\CubeManager.h"
#include "Level.h"

#include <string>

const Vector3 PLAYER_SPAWN_POINT_LVL1 = Vector3(0.0f, 3.f, -3.f);

class LevelOne
{
private:
	Player * m_player;
	BasicShader * m_basicShader;
	Level * m_level;
	Direct2DEngine * pD2D;

	//My managers
	WallManager * pWallManager = nullptr;
	CubeManager * pCubemanager = nullptr;


	//debug stuff
	Timer m_timer;
	unsigned int lastFPSCount = 0;
	unsigned int frameCounter = 0;
public:
	LevelOne(Direct2DEngine * pD2D) { this->pD2D = pD2D; }
	~LevelOne();

	void Update();
	void Draw();
	bool initialize(ID3D11Device * in_device, ID3D11DeviceContext* in_deviceContext, Player* player);
};

#endif // !LEVELONE_H
