#ifndef PLAYER_H
#define PLAYER_H
#include"Camera.h"
#include"..\Objects\WandModel.h"
#include "..\Helpers\AssetsPaths.h"
#include "..\Importer\ObjectImporter.h"
#include "..\Collision\CollisionBox.h"
#include "..\Levels\LevelState.h"
#include "Inventory.h"

class Player
{
private:

	//Inventory
	Camera* cam;

	//Wand
	WandModel* wand;

	//Inventory
	Inventory* inventory;

	//Shader
	BasicShader* m_basicShader;

	//Bounding box
	DirectX::BoundingOrientedBox* avatar;	

	//D3D11 Stuff
	ID3D11Device* dev;
	ID3D11DeviceContext* devC;

	//game stuff
	XMFLOAT3 lastFramePos;

	bool holdingKeyPressed;
	bool realmKeyPressed;
	void switchRealm(LevelState* state);
	void inventorySelect(void);

public:
	
	Player();
	~Player();

	//Misc
	void terrainCollision(std::vector<Vector3> &vPos, std::vector<uint16_t> &indices);
	bool init(ID3D11Device* dev, ID3D11DeviceContext* devC, HWND hwnd);
	void update(void);
	void draw(void);
	void handleWallCollision(std::vector<DirectX::BoundingOrientedBox> targets);
	int synchGrabKey();
	int synchRealmKey(LevelState* state);
	void resetToLastFramePos();
	BoundingFrustum getCamFrustrum();
	void resetPlayer(const DirectX::SimpleMath::Vector3 &in_val);

	//Get
	Dimension getCurrentDimension() const;
	PUZZLE_PHASE getCurrentLevelPhase() const;
	bool getKeyPressed();
	Camera* getCam(void);
	WandModel* getWand(void);
	DirectX::BoundingOrientedBox* getAvatar();
	Inventory* getInventory() const;

	//Set

};
#endif // !PLAYER_H
