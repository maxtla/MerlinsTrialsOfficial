#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include"level.h"
#include"Enumerators.h"


class LevelManager
{
private:
	std::vector<Level> levelVec;
	std::vector<std::string> filePathOrderVec;

	ID3D11DeviceContext* deviceContext;
	ID3D11Device* device;
	ObjectImporter* importer; 

	unsigned int cLevel;
	Dimension cDimension;
	

	void setBuffers();
	void swapDimensions();
	bool initiateLevels();

public:
	LevelManager();
	~LevelManager();

	void updateCurrentLevel();

	bool initLevelManager(ID3D11Device* in_device, ID3D11DeviceContext * in_deviceContext, ObjectImporter * in_importer);
	void callSwapDimension();
	void loadNextLevel();

	unsigned int getNumOfLevels() const;


};
#endif // !LEVELMANAGER_H
