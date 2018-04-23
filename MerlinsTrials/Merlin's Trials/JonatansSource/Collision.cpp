#include "Collision.h"

XMFLOAT3 Collision::updateCollision(BoundingOrientedBox *origin, BoundingOrientedBox *target)
{
	XMFLOAT3 direction = XMFLOAT3(0, 0, 0);
	if (origin->Intersects(*target))
	{
		direction.x = origin->Center.x - target->Center.x;
		direction.y = origin->Center.y - target->Center.y;
		direction.z = origin->Center.z - target->Center.z;
	}

	return direction;
}

bool Collision::checkCollision(BoundingOrientedBox *origin, BoundingOrientedBox *target)
{
	return origin->Intersects(*target);
}

bool Collision::checkPreCollision(BoundingOrientedBox *origin, BoundingOrientedBox *target, XMFLOAT3 velocity, XMVECTOR direction)
{
	bool collide = false;
	BoundingOrientedBox test = BoundingOrientedBox(*origin);
	test.Center.x += velocity.x;
	test.Center.y += velocity.y;
	test.Center.z += velocity.z;


	if (test.Intersects(*target))
	{
		collide = true;
	}
	return collide;
}

bool Collision::checkPreCollision(BoundingOrientedBox *origin, BoundingOrientedBox *target, float velocity, XMVECTOR direction)
{
	bool collide = false;
	BoundingOrientedBox test = BoundingOrientedBox(*origin);
	
	XMVECTOR dir = XMLoadFloat3(&origin->Center);
	dir = XMVectorAdd(dir, XMVectorScale(direction, velocity));
	XMFLOAT3 dirF;
	XMStoreFloat3(&dirF, dir);
	test.Center = dirF;

		if (test.Intersects(*target))
		{
			collide = true;
		}
	return collide;
}

float Collision::updateTerrainCollision(float x, float z)
{
	float height = 0.0f;
	return height;
}

bool Collision::checkPreTerrainCollision(float x, float z)
{
	float height = 0.0f;
	return height;
}

XMVECTOR Collision::wallCollisionResponse(XMVECTOR lookDirection, XMVECTOR faceTangent, float speed)
{
	XMVECTOR result = XMVectorScale(faceTangent, speed);
	XMVECTOR direction1 = XMVector3AngleBetweenVectors(lookDirection, faceTangent);
	XMVECTOR direction2 = XMVector3AngleBetweenVectors(lookDirection, -faceTangent);


	if (XMVectorGetX(direction1) >= XMVectorGetX(direction2))
	{
		result = XMVectorScale(-faceTangent, speed);
	}

	return result;
}