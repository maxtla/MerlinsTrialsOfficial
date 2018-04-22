#pragma once
#ifndef _DIRECT2DENGINE_H
#define _DIRECT2DENGINE_H
#include "source/GEngine.h"

class Direct2DEngine
{
public:
	Direct2DEngine(GEngine * pEngine);
	~Direct2DEngine();

	

private:
	GEngine * pEngine;
};
#endif //!_DIRECT2DENGINE_H
