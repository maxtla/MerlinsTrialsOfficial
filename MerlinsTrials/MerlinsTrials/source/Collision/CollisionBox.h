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
	XMFLOAT3 indexVertices;
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
	Faces(XMVECTOR normal, XMFLOAT3 centerPos, XMVECTOR biTangent, XMVECTOR tangent, XMFLOAT3 indices)
	{
		this->normal = normal;
		this->centerPos = centerPos;
		this->biTangent = biTangent;
		this->tangent = tangent;
		this->indexVertices = indices;
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
	Faces getFace(XMVECTOR normal);
	int getFaceIndex(Faces face);
	int getClosestFace(CollisionBox* target);
	Faces getClosestFace(XMFLOAT3 target);
	Faces getClosestFace(Faces target);
	CollisionBox getWorldBox(XMMATRIX world);
	std::vector<Faces> getBoxFaces();
	XMFLOAT3 getSupportVertex(XMVECTOR normal);
	XMVECTOR getSupportNormal(XMVECTOR normal);
	int getOppositeFaceIndex(int FaceIndex);

};
#endif