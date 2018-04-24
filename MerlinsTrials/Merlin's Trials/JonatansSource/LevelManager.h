#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include"LevelOne.h"
#include"Enumerators.h"
#include"Player.h"

class LevelManager
{
private:
	LevelOne levelOne;

	ID3D11DeviceContext* deviceContext;
	ID3D11Device* device;
	ObjectImporter* importer; 

	unsigned int cLevel;
	
	bool initiateLevels();
public:
	LevelManager();
	~LevelManager();

	void updateCurrentLevel(); //draw and collision
	void changeLevel();
	bool initLevelManager(ID3D11Device* in_device, ID3D11DeviceContext * in_deviceContext, ObjectImporter * in_importer, Player* player);
	void callSwapDimension(); //call function on button hit to change draw call
	void loadNextLevel();

	unsigned int getNumOfLevels() const;


};
#endif // !LEVELMANAGER_H
