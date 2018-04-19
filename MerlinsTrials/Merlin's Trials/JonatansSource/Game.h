#ifndef GAME_H
#define GAME_H

#include"Engine.h"
#include"LevelManager.h"
#include"ObjectImporter.h"


class Game {

private:

	Camera cam;
	Engine engine;
	LevelManager lvlManager;
	ObjectImporter objImporter;

public:

	Game();
	~Game();

	void init(HINSTANCE* hInst, HWND* wHandle);
	void update(float dt);

	//Get
	Camera* getCam(void);

	//Set


};

#endif // !GAME_H
