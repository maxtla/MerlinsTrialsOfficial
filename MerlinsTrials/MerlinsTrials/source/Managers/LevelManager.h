#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include "..\Levels\LevelOne.h"
#include "..\Objects\ModelBase.h"
#include "..\Helpers\Enumerators.h"
#include "..\Player\Player.h"
#include "..\Importer\ObjectImporter.h"

class LevelOne;
class LevelManager
{
private:
	LevelOne levelOne;

	ID3D11DeviceContext* deviceContext;
	ID3D11Device* device;
	InputHandler* inputHandler;
	Timer timer;

	unsigned int cLevel;
	Dimension cDimension;
	
	void dimensionCheck(); //call function on button hit to change draw call
public:
	LevelManager();
	~LevelManager();

	void update(); //draw and collision
	void changeLevel();
	void initialize(ID3D11Device* in_device, ID3D11DeviceContext * in_deviceContext, InputHandler* in_handler, Player* in_player);

	void loadNextLevel();

	unsigned int getNumOfLevels() const;


};
#endif // !LEVELMANAGER_H
