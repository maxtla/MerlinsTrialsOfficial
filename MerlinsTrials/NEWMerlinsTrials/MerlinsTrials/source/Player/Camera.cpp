#include "stdafx.h"
#include "Camera.h"

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#endif

Camera::Camera()
{
	m_view = Matrix::Identity;
	m_projection = Matrix::Identity;
	m_orthoProj = Matrix::Identity;

	this->m_camPos = { 0.0f, 0.5f, 0.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_target = { 0.0f, 0.0f, -1.0f };
	m_camForward = { 0.0f, 0.0f, -1.0f };
	m_right = { 1.0f, 0.0f, 0.0f };
	m_yaw = 0.f;
	m_pitch = 0.f;
	m_roll = 0.f;

	m_fov = 0.f;
	m_aspect = 0.f;
	m_nearZ = 0.f;
	m_farZ = 0.f;

	m_viewWidth = 0.f;
	m_viewHeight = 0.f;
	m_orthoNearZ = 0.f;
	m_orthoFarZ = 0.f;

	m_moveSpeed = 0.001f;
	m_rotationalOffset = 0.01f;

	this->terrainHeight = 0.0f;

	GetCursorPos(&mouseLast);
}


Camera::~Camera()
{
}

void Camera::setCameraPosition(Vector3 pos)
{
	m_camPos = pos; 
}

void Camera::setCameraUp(Vector3 up)
{
	m_up = up; 
}

void Camera::setCameraTarget(Vector3 target)
{
	m_target = target; 
}

void Camera::setCameraForward(Vector3 forward)
{
	m_camForward = forward; 
	m_camForward.Normalize();

	m_up = m_camForward.Cross(m_up); 
	m_up.Normalize();
}

void Camera::setCameraRight(Vector3 right)
{
	m_right = right; 
	m_right.Normalize();

	m_up = m_right.Cross(m_camForward); 
	m_up.Normalize();
}

bool Camera::createViewMatrix(Vector3 eye, Vector3 target, Vector3 up)
{
	//create a LH view matrix
	this->m_view = DirectX::XMMatrixLookAtRH(eye, target, up);

	//set pos, target and up
	this->m_camPos = eye;
	this->m_target = target;
	this->m_up = up;
	this->m_up.Normalize();

	//calculate the forward and right vector (construct the final coordinatsystem)
	this->m_camForward = target - eye;
	this->m_camForward.Normalize();
	this->m_right = this->m_up.Cross(this->m_camForward);
	this->m_right.Normalize();

	return true;
}

bool Camera::createProjectionMatrix(float fov, float aspect, float nearZ, float farZ)
{
	//create the LH perspective projection matrix
	this->m_projection = DirectX::XMMatrixPerspectiveFovRH(fov, aspect, nearZ, farZ);

	//set related components
	this->m_fov = fov;
	this->m_aspect = aspect;
	this->m_nearZ = nearZ;
	this->m_farZ = farZ;

	return true;
}

bool Camera::createOrthoMatrix(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	//create the LH orthograpic matrix
	this->m_orthoProj = DirectX::XMMatrixOrthographicRH(viewWidth, viewHeight, nearZ, farZ);

	//set related components
	this->m_viewWidth = viewWidth;
	this->m_viewHeight = viewHeight;
	this->m_orthoNearZ = nearZ;
	this->m_orthoFarZ = farZ;

	return true;
}

void Camera::update()
{
	//start by updating the position if necessary
	if (m_timer.update())
	{
		float dt = m_timer.frameDiff();
		m_timer.reset();

		float width = (windowRect.right - windowRect.left)*0.5;
		float height = (windowRect.bottom - windowRect.top)*0.5;
		float mouseX = width;
		float mouseY = height;

		if (GetCursorPos(&mouseNew))
		{
			mouseX -= mouseNew.x;
			mouseY -= mouseNew.y;
			SetCursorPos(width, height);
		}

		if (GetAsyncKeyState(0x57))
		{
			m_camPos += m_camForward * m_moveSpeed * dt;
			m_target += m_camForward * m_moveSpeed * dt;
		}
		if (GetAsyncKeyState(0x53))
		{
			m_camPos -= m_camForward * m_moveSpeed * dt;
			m_target -= m_camForward * m_moveSpeed * dt;
		}
		if (GetAsyncKeyState(0x44))
		{
			m_camPos -= m_right * m_moveSpeed * dt;
			m_target -= m_right * m_moveSpeed * dt;
		}
		if (GetAsyncKeyState(0x41))
		{
			m_camPos += m_right * m_moveSpeed * dt;
			m_target += m_right * m_moveSpeed * dt;
		}

		m_yaw += mouseX * m_rotationalOffset * dt;
		m_pitch -= mouseY * m_rotationalOffset * dt;
			
		//Update height position on terrain
		if (this->terrainHeight != this->m_camPos.y) {

			//Get height difference and add offset
			float heightPos = (this->terrainHeight - this->m_camPos.y) + 0.5f;
			this->m_camPos.y += heightPos;

		}

		clampToHalfPI(this->m_pitch);

		//First person camera
		Matrix camRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, 0.0f);
		this->m_target = DirectX::XMVector3Transform(DefaultForward, camRotationMatrix);
		this->m_target.Normalize();

		Matrix rotY = Matrix::CreateRotationY(this->m_yaw);
		m_right = DirectX::XMVector3TransformCoord(DefaultRight, rotY);
		m_camForward = DirectX::XMVector3TransformCoord(DefaultForward, rotY);
		m_up = DirectX::XMVector3TransformCoord(this->m_up, rotY);

		this->m_right.Normalize();
		this->m_camForward.Normalize();
		this->m_up.Normalize();

		m_target += m_camPos;
		m_view = DirectX::XMMatrixLookAtRH(m_camPos, m_target, m_up);
	}
}

void Camera::clampToHalfPI(float & value)
{
	value = std::fmax(-0.3f*DirectX::XM_PI, std::fmin(value, 0.3f*DirectX::XM_PI));
}
