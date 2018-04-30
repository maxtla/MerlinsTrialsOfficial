#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <d3d11.h>
#include "SimpleMath.h"
#include "..\Helpers\Timer.h"

using namespace DirectX::SimpleMath;

//The camera class soley contains stateful information such as:
// current position and other related vector
// matrices for its view and projections
// Angular components such as Yaw (around Z), Pitch (around Y) and Roll (around X)
//to manipulate any camera with inputs make use of the Get and Set functions
//and/or call the create function to set a certain matrix and all the related components


//global constants axis-Vectors that are universal 
const Vector3 DefaultForward = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 DefaultRight = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 DefaultUp = Vector3(0.0f, 1.0f, 0.0f);

class Camera
{
public:
	Camera();
	~Camera();
	//PUBLIC MEMEBERS

	//PUBLIC METHODS
	//set functions
	void setViewMatrix(Matrix view) { m_view = view; }
	void setProjectionMatrix(Matrix proj) { m_projection = proj; }
	void setOrthoProjecMatrix(Matrix ortho) { m_orthoProj = ortho; }
	void setCameraPosition(Vector3 pos);
	void setCameraUp(Vector3 up);
	void setCameraTarget(Vector3 target);
	void setCameraForward(Vector3 forward);
	void setCameraRight(Vector3 right);
	void setCameraMoveSpeed(float ms) { m_moveSpeed = ms; }
	void setCameraYaw(float yaw) { m_yaw = yaw; }
	void setCameraPitch(float pitch) { m_pitch = pitch; }
	void setCameraRoll(float roll) { m_roll = roll; }
	void setRotationalOffset(float offset) { m_rotationalOffset = offset; }
	void setYawPitchRoll(float yaw, float pitch, float roll) { m_yaw = yaw; m_pitch = pitch; m_roll = roll; }
	void setFOV(float fov) { m_fov = fov; this->m_projection = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearZ, m_farZ); }
	void setAspectRatio(float aspect) { m_aspect = aspect; this->m_projection = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearZ, m_farZ); }
	void setNearZ(float nearZ) { m_nearZ = nearZ; this->m_projection = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearZ, m_farZ); }
	void setFarZ(float farZ) { m_farZ = farZ; this->m_projection = DirectX::XMMatrixPerspectiveFovLH(m_fov, m_aspect, m_nearZ, m_farZ); }
	void setOrthoViewWidth(float viewWidth) { m_viewWidth = viewWidth;  this->m_orthoProj = DirectX::XMMatrixOrthographicLH(m_viewWidth, m_viewHeight, m_orthoNearZ, m_orthoFarZ); }
	void setOrthoViewHeight(float viewHeight) { m_viewHeight = viewHeight; this->m_orthoProj = DirectX::XMMatrixOrthographicLH(m_viewWidth, m_viewHeight, m_orthoNearZ, m_orthoFarZ); }
	void setOrthoNearZ(float nearZ) { m_orthoNearZ = nearZ; this->m_orthoProj = DirectX::XMMatrixOrthographicLH(m_viewWidth, m_viewHeight, m_orthoNearZ, m_orthoFarZ); }
	void setOrthoFarZ(float farZ) { m_orthoFarZ = farZ; this->m_orthoProj = DirectX::XMMatrixOrthographicLH(m_viewWidth, m_viewHeight, m_orthoNearZ, m_orthoFarZ); }
	void setTimerCount(double count) { m_timer.setUpdateCount(count); }
	
	void setMoveForward(bool move) { m_moveForward = move; }
	void setMoveBackward(bool move) { m_moveBackward = move; }
	void setMoveRight(bool move) { m_moveRight = move; }
	void setMoveLeft(bool move) { m_moveLeft = move; }
	void setRotated(bool rotated) { m_rotated = rotated; }
	void setLastMousePos(Vector2 pos) { m_lastMousePos = pos; }

	//get functions
	Matrix getView() const { return m_view; }
	Matrix getProjection() const { return m_projection; }
	Matrix getOrthoProj() const { return m_orthoProj; }
	Vector3 getCamPos() const { return m_camPos; }
	Vector3 getCamUp() const { return m_up; }
	Vector3 getCamTarget() const { return m_target; }
	Vector3 getCamForward() const { return m_camForward; }
	Vector3 getCamRight() const { return m_right; }
	float getMoveSpeed() const { return m_moveSpeed; }
	float getCamYaw() const { return m_yaw;  }
	float getCamPitch() const { return m_pitch; }
	float getCamRoll() const { return m_roll; }
	float getRotationalOffset() const { return m_rotationalOffset; }
	float getFOV() const { return m_fov; }
	float getAspectRatio() const { return m_aspect; }
	float getNearZ() const { return m_nearZ; }
	float getFarZ() const { return m_farZ; }
	float getOrthoViewWidth() const { return m_viewWidth; }
	float getOrthoViewHeight() const { return m_viewHeight; }
	float getOrthoNearZ() const { return m_orthoNearZ; }
	float getOrthoFarZ() const { return m_orthoFarZ; }

	//create functions
	bool createViewMatrix(Vector3 eye, Vector3 target, Vector3 up);
	bool createProjectionMatrix(float fov, float aspect, float nearZ, float farZ);
	bool createOrthoMatrix(float viewWidth, float viewHeight, float nearZ, float farZ);

	//update function (rotation applied to view)
	void update();

	//initialization
	void init() { m_timer.startTimer(); }

private:
	//PRIVATE MEMBERS
	Matrix m_view;
	Matrix m_projection;
	Matrix m_orthoProj;

	//camera view components
	Vector3 m_camPos;
	Vector3 m_up;
	Vector3 m_target;
	Vector3 m_camForward;
	Vector3 m_right;
	float m_moveSpeed;
	float m_yaw;
	float m_pitch;
	float m_roll;
	float m_rotationalOffset;

	//perpective projection components
	float m_fov;
	float m_aspect;
	float m_nearZ;
	float m_farZ;

	//orthographical perspective components
	float m_viewWidth;
	float m_viewHeight;
	float m_orthoNearZ;
	float m_orthoFarZ;

	//timer
	Timer m_timer;

	//boolean for handling movement and rotations
	bool m_moveForward = false;
	bool m_moveBackward = false;
	bool m_moveRight = false;
	bool m_moveLeft = false;
	bool m_rotated = false;
	Vector2 m_lastMousePos = Vector2::Zero;

	//PRIVATE METHODS
	void clampToHalfPI(float& value);
};
#endif
