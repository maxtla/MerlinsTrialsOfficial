#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H
#include <DirectXMath.h>
#include <DirectXCollision.h>
#include <vector>
using namespace DirectX;

struct Faces
{
	XMVECTOR normal; //local Z Axis
	XMFLOAT3 centerPos;
	XMVECTOR biTangent; //local Y Axis
	XMVECTOR tangent; //local X Axis
	
	Faces(XMVECTOR normal, XMFLOAT3 centerPos)
	{
		this->normal = normal;
		this->centerPos = centerPos;
	}
	Faces(XMVECTOR normal, XMFLOAT3 centerPos, XMVECTOR biTangent, XMVECTOR tangent)
	{
		this->normal = normal;
		this->centerPos = centerPos;
		this->biTangent = biTangent;
		this->tangent = tangent;
	}
	bool operator==(const Faces compare)
	{
		if (XMVector3Equal(this->normal, compare.normal))
		{
			if (XMVector3Equal(XMLoadFloat3(&this->centerPos), XMLoadFloat3(&compare.centerPos)))
			{
				if (XMVector3Equal(this->biTangent, compare.biTangent) && XMVector3Equal(this->tangent, compare.tangent))
				{
					return true;
				}
			}
			
		}
		return false;
	}
};

class CollisionBox
{
private:
	BoundingOrientedBox box;
	std::vector<Faces> boxFaces;
	void generateFaces();
	void updateFacePositions();
public:
	CollisionBox();
	CollisionBox(XMFLOAT3 position, XMFLOAT3 extents, XMFLOAT4 orientation);
	CollisionBox(BoundingOrientedBox boundingBox);
	CollisionBox(XMFLOAT3* points, int size);
	~CollisionBox();
	BoundingOrientedBox getBoundingBox();
	void setBoundingBox(BoundingOrientedBox boundingBox);
	void setPosition(XMFLOAT3 position);
	Faces getFaceAt(int pos);
	int getFaceIndex(Faces face);
	Faces getClosestFace(CollisionBox* target);

};
#endif