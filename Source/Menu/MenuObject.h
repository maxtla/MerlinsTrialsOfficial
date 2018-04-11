#pragma once
#ifndef MENUOBJECT_H
#define MENUOBJECT_H
#include <DirectXMath.h>
#include "GridMenu.h"
#include <string>

using namespace std;
using namespace DirectX;

class MenuObject
{
private:
	int ID;
	XMFLOAT2 pos;
	XMFLOAT2 size;
public:
	MenuObject(int ID, XMFLOAT2 pos, XMFLOAT2 size);
	virtual ~MenuObject();
	XMFLOAT2 getSize();
	XMFLOAT2 getPos();
	int getID();
};

class TextBox : public MenuObject
{
private:
	string text;
public:
	TextBox(string text, int ID, XMFLOAT2 pos, XMFLOAT2 size);
	virtual ~TextBox();
	string getText();
};

class Button : public TextBox
{
private:
	enum state {HOVERED, PRESSED, RELEASED};
public:
	Button(string text, int ID, XMFLOAT2 pos, XMFLOAT2 size);
	Button(int ID, XMFLOAT2 pos, XMFLOAT2 size);
	virtual ~Button();
	enum getState();
	void setState(enum state);
};

class SubMenu : public MenuObject
{
private:
	GridMenu * menu;
public:
	SubMenu(int ID, XMFLOAT2 pos, XMFLOAT2 size, int listSize);
	virtual ~Button();
	enum getState();
	void setState(enum state);
};