#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	m_view = Matrix::Identity;
	m_projection = Matrix::Identity;
	m_orthoProj = Matrix::Identity;

	m_camPos = Vector3::Zero;
	m_up = Vector3::Zero;
	m_target = Vector3::Zero;
	m_camForward = Vector3::Zero;
	m_right = Vector3::Zero;
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
}


Camera::~Camera()
{
}

void Camera::setCameraPosition(Vector3 pos)
{
	m_camPos = pos; 
	this->m_view = DirectX::XMMatrixLookAtLH(m_camPos, m_target, m_up); 
}

void Camera::setCameraUp(Vector3 up)
{
	m_up = up; 
	this->m_view = DirectX::XMMatrixLookAtLH(m_camPos, m_target, m_up);
}

void Camera::setCameraTarget(Vector3 target)
{
	m_target = target; 
	this->m_view = DirectX::XMMatrixLookAtLH(m_camPos, m_target, m_up);
}

void Camera::setCameraForward(Vector3 forward)
{
	m_camForward = forward; 
	m_camForward.Normalize();

	m_up = m_camForward.Cross(m_up); 
	m_up.Normalize();

	this->m_view = DirectX::XMMatrixLookAtLH(m_camPos, m_target, m_up);
}

void Camera::setCameraRight(Vector3 right)
{
	m_right = right; 
	m_right.Normalize();

	m_up = m_right.Cross(m_camForward); 
	m_up.Normalize();

	this->m_view = DirectX::XMMatrixLookAtLH(m_camPos, m_target, m_up);
}

bool Camera::createViewMatrix(Vector3 eye, Vector3 target, Vector3 up)
{
	//create a LH view matrix
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
	this->m_orthoProj = DirectX::XMMatrixOrthographicLH(viewWidth, viewHeight, nearZ, farZ);

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
		if (m_moveForward)
		{
			m_camPos -= m_camForward * m_moveSpeed;
			m_target -= m_camForward * m_moveSpeed;
		}
		if (m_moveBackward)
		{
			m_camPos += m_camForward * m_moveSpeed;
			m_target += m_camForward * m_moveSpeed;
		}
		if (m_moveRight)
		{
			m_camPos -= m_right * m_moveSpeed;
			m_target -= m_right * m_moveSpeed;
		}
		if (m_moveLeft)
		{
			m_camPos += m_right * m_moveSpeed;
			m_target += m_right * m_moveSpeed;
		}

		if (m_rotated)
		{
			m_yaw += m_lastMousePos.x * m_rotationalOffset;
			m_pitch += m_lastMousePos.y * m_rotationalOffset;

			clampToHalfPI(this->m_pitch);


			Matrix camRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, m_roll);

			m_right = DirectX::XMVector3TransformCoord(DefaultRight, camRotationMatrix);
			m_camForward = DirectX::XMVector3TransformCoord(DefaultForward, camRotationMatrix);

			m_right.Normalize();
			m_camForward.Normalize();

			m_up = m_right.Cross(m_camForward);
			m_up.Normalize();

			m_target = m_camPos + m_camForward;

			m_view = DirectX::XMMatrixLookAtLH(m_camPos, m_target, m_up);
		}
		else
			m_view = DirectX::XMMatrixLookAtLH(m_camPos, m_target, m_up);
	}
}

void Camera::clampToHalfPI(float & value)
{
	value = std::fmax(-0.5f*DirectX::XM_PI, std::fmin(value, 0.5f*DirectX::XM_PI));
}
