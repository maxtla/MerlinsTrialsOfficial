#ifndef PLAYER_H
#define PLAYER_H
#include"Camera.h"

class Player
{
private:
	Camera * camera;

public:
	Player();
	~Player();

	Camera* getCamera();
};
#endif // !PLAYER_H
