#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Keyboard.h"
#include "Mouse.h"
//use a direct input approach where each class object is modified by the current matched input message per frame
#include "Camera.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();
	//PUBLIC MEMBERS
	//The message is fetched and updated everytime GetMessage gets something from the message queue thread
	//PUBLIC METHODS
	void initialize(HWND hwnd);
	void update();
	void resetMouseMode();
	//use the updated current message and check if the input affects our objects
	void handleCameraInput(Camera * pCamera);
	void wndChanged(bool &changed);
	bool inMenu = false;
private:
	//PRIVATE MEMBERS
	HWND hwnd;
	MSG m_msg;
	UINT currentMsg;
	BOOL hasMsg;
	
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Mouse> m_mouse;
	DirectX::Mouse::State m_mouseState;
	DirectX::Keyboard::KeyboardStateTracker m_tracker;
	//PRIVATE METHODS
	void clampToPi(float &value);
};

enum CAMERA_INPUT_KEYS
{
	KEY_W = DirectX::Keyboard::W,
	KEY_A = DirectX::Keyboard::A,
	KEY_S = DirectX::Keyboard::S,
	KEY_D = DirectX::Keyboard::D
};

#endif //INPUTHANDLER_H
