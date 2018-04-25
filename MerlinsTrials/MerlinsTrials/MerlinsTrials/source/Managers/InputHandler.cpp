#include "stdafx.h"
#include "InputHandler.h"


InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()	
{
	m_mouse.release();
	m_keyboard.release();
}

void InputHandler::initialize(HWND hwnd)
{
	m_keyboard = std::make_unique<DirectX::Keyboard>();
	m_mouse = std::make_unique<DirectX::Mouse>();

	m_mouse->SetWindow(hwnd);
	m_mouseState = m_mouse->GetState();

	this->hwnd = hwnd;
}

void InputHandler::update()
{
	if (inMenu && m_mouse->GetState().positionMode == DirectX::Mouse::MODE_RELATIVE)
		m_mouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);

}

void InputHandler::resetMouseMode()
{
	//this->m_mouse->SetMode(DirectX::Mouse::Mode::MODE_ABSOLUTE);
}

void InputHandler::handleCameraInput(Camera * pCamera)
{
	auto kbState = m_keyboard->GetState();
	auto mState = m_mouse->GetState();

	m_tracker.Update(kbState);

	if (m_tracker.IsKeyPressed(DirectX::Keyboard::W))
		pCamera->setMoveForward(true);
	else if (m_tracker.IsKeyReleased(DirectX::Keyboard::W))
		pCamera->setMoveForward(false);
	if (m_tracker.IsKeyPressed(DirectX::Keyboard::S))
		pCamera->setMoveBackward(true);
	else if (m_tracker.IsKeyReleased(DirectX::Keyboard::S))
		pCamera->setMoveBackward(false);
	if (m_tracker.IsKeyPressed(DirectX::Keyboard::D))
		pCamera->setMoveRight(true);
	else if (m_tracker.IsKeyReleased(DirectX::Keyboard::D))
		pCamera->setMoveRight(false);
	if (m_tracker.IsKeyPressed(DirectX::Keyboard::A))
		pCamera->setMoveLeft(true);
	else if (m_tracker.IsKeyReleased(DirectX::Keyboard::A))
		pCamera->setMoveLeft(false);


	if (mState.positionMode == DirectX::Mouse::MODE_RELATIVE)
	{	
		if (mState.x != 0 || mState.y != 0)
		{
			pCamera->setRotated(true);
			pCamera->setLastMousePos(Vector2(mState.x, mState.y));
		}
		else
			pCamera->setRotated(false);
	}

	//set the state to relative in case it was changed to absolute for ex. entering Menu
	if (mState.positionMode == DirectX::Mouse::MODE_ABSOLUTE && !inMenu)
		m_mouse->SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void InputHandler::wndChanged(bool & changed)
{
	if (changed)
	{
		m_mouse->SetMode(DirectX::Mouse::MODE_ABSOLUTE);
	}
}

void InputHandler::clampToPi(float & value)
{
	value = std::fmax(-0.5f*DirectX::XM_PI, std::fmin(value, 0.5f*DirectX::XM_PI));
}
