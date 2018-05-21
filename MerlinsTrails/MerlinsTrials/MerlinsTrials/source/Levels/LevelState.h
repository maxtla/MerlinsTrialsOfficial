#pragma once
#ifndef LEVELSTATE_H
#define LEVELSTATE_H
#include"..\Helpers\Enumerators.h"
#include"..\Helpers\AssetsPaths.h"

class LevelState
{
private:
	Dimension cDimension; //current Dimension NORMAL, OTHER
	PUZZLE_PHASE cPhase; //current level phase FIRST, SECOND, END
	CURRENT_LEVEL cLevel; 
	TIMER cTimer;

	bool isEndScreen;
	unsigned int fCubes = 0; //finnished cubes
	unsigned int cubesToWin = NR_OF_CUBES; //4

public:
	LevelState();
	~LevelState();
	
	//MISC
	void update();
	bool checkWinCondition() const;
	bool checkCubeStatus();
	void changeLevel();
	
	//SETS
	void setLevel(const CURRENT_LEVEL &in_cLevel);
	void setDimension(const Dimension &in_cDim);
	void setPhase(const PUZZLE_PHASE &in_cPhase);
	void setFCubes(const unsigned int &in_value);
	void addFCubes(const unsigned int &in_addTo);
	void subFCubes(const int &in_subTo);
	void setTimer(const TIMER &in_cTimer);
	void setIsEndScreen(const bool &in_value);

	//GETS
	Dimension getDimension() const;
	PUZZLE_PHASE getPhase() const;
	CURRENT_LEVEL getLevel() const;
	TIMER getTimer() const;
	unsigned int getFCubes() const;
	unsigned int getCubesToWin() const;
	bool getIsEndScreen() const;

};
#endif // !LEVELSTATE_H
