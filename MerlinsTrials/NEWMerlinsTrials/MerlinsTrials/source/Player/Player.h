#ifndef PLAYER_H
#define PLAYER_H
#include"Camera.h"
#include"..\Objects\WandModel.h"
#include "..\Helpers\AssetsPaths.h"
#include "..\Importer\ObjectImporter.h"
#include "..\Collision\CollisionBox.h"

class Player
{
private:

	Camera * cam;
	WandModel* wand;
	BasicShader * m_basicShader;
	DirectX::BoundingOrientedBox* avatar;
	//D3D11 Stuff
	ID3D11Device* dev;
	ID3D11DeviceContext* devC;
	
	//game stuff
	Dimension cDimension;
	PUZZLE_PHASE cPhase;
	
	bool holdingKeyPressed;
	bool realmKeyPressed;
	void switchRealm();
public:
	
	Player();
	~Player();

	//Misc
	void terrainCollision(std::vector<Vector3> &vPos, std::vector<uint16_t> &indices);
	bool init(ID3D11Device* dev, ID3D11DeviceContext* devC, HWND hwnd);
	void update(void);
	void draw(void);
	void handleWallCollision(std::vector<DirectX::BoundingOrientedBox> targets);
	int synchKey();
	//Get
	Dimension getCurrentDimension() const;
	PUZZLE_PHASE getCurrentLevelPhase() const;
	bool getKeyPressed();
	Camera* getCam(void);
	WandModel* getWand(void);
	DirectX::BoundingOrientedBox* getAvatar();
	  
	//Set
	void setCurrentDimension(const Dimension &in_dim);
	void setCurrentLevelPhase(const PUZZLE_PHASE &in_phase);

};
#endif // !PLAYER_H
