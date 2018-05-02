#ifndef PLAYER_H
#define PLAYER_H
#include"Camera.h"

class Player
{
private:
	Camera * camera;

	bool holdingItem = false;

public:
	Player();
	~Player();
};
#endif // !PLAYER_H
