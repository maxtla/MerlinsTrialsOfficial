#include "stdafx.h"
#include "LevelState.h"

//check how many cubes are finnished
//and trigger phase shift ie "puzzle 2" of this level
bool LevelState::checkCubeStatus()
{
	if (this->checkWinCondition())
	{
		switch (this->cPhase)
		{
		case PUZZLE_PHASE::FIRST:
		{
			this->cPhase = PUZZLE_PHASE::SECOND;
			this->cDimension = Dimension::NORMAL;
		}
			break;
		case PUZZLE_PHASE::SECOND:
		{
			this->cPhase = PUZZLE_PHASE::END;
			this->cDimension = Dimension::NORMAL;
		}
			break;
		case PUZZLE_PHASE::END:
		{
			
		}
			break;	
		}

		this->fCubes = 0;
		return true;
	}

	return false;
}

void LevelState::changeLevel()
{
	switch (this->cLevel)
	{
	case CURRENT_LEVEL::ONE:
		this->cLevel = CURRENT_LEVEL::TWO;
		this->cPhase = PUZZLE_PHASE::FIRST;
		break;
	case CURRENT_LEVEL::TWO:
		this->cLevel = CURRENT_LEVEL::THREE;
		this->cPhase = PUZZLE_PHASE::FIRST;
		break;
	}
}

LevelState::LevelState()
{
	this->cDimension = Dimension::NORMAL;
	this->cPhase = PUZZLE_PHASE::FIRST;
	this->cLevel = CURRENT_LEVEL::ONE;
	this->cTimer = TIMER::INACTIVE;
	this->isEndScreen = false;
}

LevelState::~LevelState()
{
}

void LevelState::update()
{

}

bool LevelState::checkWinCondition() const
{
	return this->fCubes == this->cubesToWin;
}

void LevelState::setLevel(const CURRENT_LEVEL & in_cLevel)
{
	this->cLevel = in_cLevel;
}

void LevelState::setDimension(const Dimension & in_cDim)
{
	this->cDimension = in_cDim;
}

void LevelState::setPhase(const PUZZLE_PHASE & in_cPhase)
{
	this->cPhase = in_cPhase;
}

void LevelState::setFCubes(const unsigned int & in_value)
{
	this->fCubes = in_value;
}

void LevelState::addFCubes(const unsigned int & in_addTo)
{
	this->fCubes += in_addTo;
}

void LevelState::subFCubes(const int & in_subTo)
{
	this->fCubes -= in_subTo;
	if (this->fCubes < 0)
	{
		this->fCubes = 0;
	}
}

void LevelState::setTimer(const TIMER & in_cTimer)
{
	this->cTimer = in_cTimer;
}

void LevelState::setIsEndScreen(const bool & in_value)
{
	this->isEndScreen = in_value;
}

Dimension LevelState::getDimension() const
{
	return this->cDimension;
}

PUZZLE_PHASE LevelState::getPhase() const
{
	return this->cPhase;
}

CURRENT_LEVEL LevelState::getLevel() const
{
	return this->cLevel;
}

TIMER LevelState::getTimer() const
{
	return this->cTimer;
}

unsigned int LevelState::getFCubes() const
{
	return this->fCubes;
}

unsigned int LevelState::getCubesToWin() const
{
	return this->cubesToWin;
}

bool LevelState::getIsEndScreen() const
{
	return this->isEndScreen;
}
