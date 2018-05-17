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
	this->frustrum = new DirectX::BoundingFrustum();
}


Camera::~Camera()
{
	delete this->frustrum;
	this->frustrum = nullptr;
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

void Camera::updateFrustum(Matrix rotation)
{
	this->frustrum->Origin = this->m_camPos;
	this->frustrum->Orientation = DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(rotation);//DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(this->m_pitch, this->m_yaw, 0);
}

DirectX::BoundingFrustum Camera::setLHFrustrum()
{
	Matrix projectionLH = this->m_projection;
	projectionLH._12 = this->m_projection._13;
	projectionLH._13 = this->m_projection._12;

	projectionLH._21 = this->m_projection._31;
	projectionLH._22 = this->m_projection._33;
	projectionLH._23 = this->m_projection._32;

	projectionLH._31 = this->m_projection._21;
	projectionLH._32 = this->m_projection._23;
	projectionLH._33 = this->m_projection._22;

	projectionLH._42 = this->m_projection._43;
	projectionLH._43 = this->m_projection._42;

	return DirectX::BoundingFrustum(projectionLH);
}

bool Camera::createViewMatrix(Vector3 eye, Vector3 target, Vector3 up)
{
	//create a RH view matrix
	this->m_view = DirectX::XMMatrixLookAtLH(eye, target, up);

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
	//create the RH perspective projection matrix
	this->m_projection = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);

	//set related components
	this->m_fov = fov;
	this->m_aspect = aspect;
	this->m_nearZ = nearZ;
	this->m_farZ = farZ;

	return true;
}

bool Camera::createOrthoMatrix(float viewWidth, float viewHeight, float nearZ, float farZ)
{
	//create the RH orthograpic matrix
	this->m_orthoProj = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);

	//set related components
	this->m_viewWidth = viewWidth;
	this->m_viewHeight = viewHeight;
	this->m_orthoNearZ = nearZ;
	this->m_orthoFarZ = farZ;

	return true;
}

void Camera::createFrustrum()
{
	this->frustrum = new DirectX::BoundingFrustum(this->m_projection);
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

		if (GetAsyncKeyState(KEY::W))
		{
			m_camPos += m_camForward * m_moveSpeed * dt;
			m_target += m_camForward * m_moveSpeed * dt;
		}
		if (GetAsyncKeyState(KEY::S))
		{
			m_camPos -= m_camForward * m_moveSpeed * dt;
			m_target -= m_camForward * m_moveSpeed * dt;
		}
		if (GetAsyncKeyState(KEY::D))
		{
			m_camPos += m_right * m_moveSpeed * dt;
			m_target += m_right * m_moveSpeed * dt;
		}
		if (GetAsyncKeyState(KEY::A))
		{
			m_camPos -= m_right * m_moveSpeed * dt;
			m_target -= m_right * m_moveSpeed * dt;
		}

		m_yaw -= mouseX * m_rotationalOffset * dt;
		m_pitch -= mouseY * m_rotationalOffset * dt;
			
		//Update height position on terrain
		if (!this->isFloating && this->terrainHeight != this->m_camPos.y) {

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
		m_view = DirectX::XMMatrixLookAtLH(m_camPos, m_target, m_up);
		this->updateFrustum(camRotationMatrix);
	}
}

void Camera::clampToHalfPI(float & value)
{
	value = std::fmax(-0.3f*DirectX::XM_PI, std::fmin(value, 0.3f*DirectX::XM_PI));
}
