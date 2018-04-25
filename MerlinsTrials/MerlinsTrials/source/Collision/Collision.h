#ifndef COLLISION_H
#define COLLISION_H
#include <DirectXMath.h>
#include <DirectXCollision.h>
using namespace DirectX;

class Collision
{
private:
	
public:
	XMFLOAT3 updateCollision(BoundingOrientedBox *origin, BoundingOrientedBox *target);
	bool checkCollision(BoundingOrientedBox *origin, BoundingOrientedBox *target);
	float updateTerrainCollision(float x, float z);
	bool checkPreTerrainCollision(float x, float z);
	bool checkPreCollision(BoundingOrientedBox *origin, BoundingOrientedBox *target, XMFLOAT3 velocity, XMVECTOR direction);
	bool checkPreCollision(BoundingOrientedBox *origin, BoundingOrientedBox *target, float velocity, XMVECTOR direction);
	XMVECTOR wallCollisionResponse(XMVECTOR lookDirection, XMVECTOR faceTangent, float speed);
};
#endif
