#pragma once
#ifndef GRIDMENU_H
#define GRIDMENU_H
#include <DirectXMath.h>

using namespace DirectX;

class GridMenu
{
private:
	bool focus;
	XMFLOAT2 gridPos;
	XMFLOAT2 gridSize;
	XMFLOAT2 tileSize;
	int* grid;
public:
	GridMenu(XMFLOAT2 gridPos, XMFLOAT2 gridSize, int tileSize);
	XMFLOAT2 getGridSize();
	int getID(XMFLOAT2 gridPos);
	bool addToGrid(XMFLOAT2 gridPos, int ID);
	void emptyGrid();
	bool isFocused();
	void setFocus(bool focus);
};