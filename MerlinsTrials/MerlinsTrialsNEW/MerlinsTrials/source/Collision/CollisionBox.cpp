#include "stdafx.h"
#include "CollisionBox.h"

CollisionBox::CollisionBox()
{
	this->box = BoundingOrientedBox(XMFLOAT3(), XMFLOAT3(), XMFLOAT4());
	XMStoreFloat4(&this->box.Orientation, XMQuaternionRotationMatrix(XMMatrixRotationY(0)));
}


CollisionBox::CollisionBox(XMFLOAT3 position, XMFLOAT3 extents, XMFLOAT4 orientation)
{
	this->box = BoundingOrientedBox(position, extents, orientation);
	if (orientation.x == 0 && orientation.y == 0 && orientation.z == 0 && orientation.w == 0)
	{
		XMStoreFloat4(&this->box.Orientation,XMQuaternionRotationMatrix(XMMatrixRotationY(0)));
	}
	generateFaces();
}
CollisionBox::CollisionBox(BoundingOrientedBox boundingBox)
{
	this->box = BoundingOrientedBox(boundingBox);
	if (boundingBox.Orientation.x == 0 && boundingBox.Orientation.y == 0 && boundingBox.Orientation.z == 0 && boundingBox.Orientation.w == 0)
	{
		XMStoreFloat4(&this->box.Orientation, XMQuaternionRotationMatrix(XMMatrixRotationY(0)));
	}
	generateFaces();
}

CollisionBox::CollisionBox(XMFLOAT3 *points, int size)
{
	BoundingOrientedBox object;
	object.CreateFromPoints(object, size, points,sizeof(XMFLOAT3));
	this->box = object;
	generateFaces();
}

CollisionBox::~CollisionBox()
{
	this->boxFaces.clear();
}

void CollisionBox::generateFaces()
{
	if (!this->boxFaces.empty())
	{
		this->boxFaces.clear();
	}
	XMFLOAT3 Corners[this->box.CORNER_COUNT];

	this->box.GetCorners(Corners);
	XMVECTOR points[8];
	for (int i = 0; i < this->box.CORNER_COUNT; i++)
	{
		points[i] = XMLoadFloat3(&Corners[i]);
	}

	//BackFace
	XMVECTOR biTangent, tangent, dir;
	biTangent = XMVectorSubtract(points[3], points[0]);
	tangent = XMVectorSubtract(points[1], points[0]);
	dir = XMVector3Cross(tangent, biTangent);
	dir = XMVector3Normalize(dir);
	XMFLOAT3 pos;
	pos.x = Corners[0].x + ((Corners[1].x - Corners[0].x) / 2);
	pos.y = Corners[0].y + ((Corners[3].y - Corners[0].y) / 2);
	pos.z = Corners[0].z;
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent));
	//FrontFace
	biTangent = XMVectorSubtract(points[7], points[4]);
	tangent = XMVectorSubtract(points[5], points[4]);
	dir = XMVector3Cross(biTangent, tangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[4].x + ((Corners[5].x - Corners[4].x) / 2);
	pos.y = Corners[4].y + ((Corners[7].y - Corners[4].y) / 2);
	pos.z = Corners[4].z;
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent));

	//TopFace
	biTangent = XMVectorSubtract(points[3], points[7]);
	tangent = XMVectorSubtract(points[6], points[7]);
	dir = XMVector3Cross(biTangent, tangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[7].x + ((Corners[6].x - Corners[7].x) / 2);
	pos.y = Corners[7].y;
	pos.z = Corners[7].z + ((Corners[3].z - Corners[7].z) / 2);
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent));
	//BottomFace
	biTangent = XMVectorSubtract(points[0], points[4]);
	tangent = XMVectorSubtract(points[5], points[4]);
	dir = XMVector3Cross(tangent, biTangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[4].x + ((Corners[5].x - Corners[4].x) / 2);
	pos.y = Corners[4].y;
	pos.z = Corners[4].z + ((Corners[0].z - Corners[4].z) / 2);
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent));

	//RightFace
	biTangent = XMVectorSubtract(points[6], points[5]);
	tangent = XMVectorSubtract(points[1], points[5]);
	dir = XMVector3Cross(biTangent, tangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[5].x;
	pos.y = Corners[5].y + ((Corners[6].y - Corners[5].y) / 2);
	pos.z = Corners[5].z + ((Corners[1].z - Corners[5].z) / 2);
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent));
	//LeftFace
	biTangent = XMVectorSubtract(points[7], points[4]);
	tangent = XMVectorSubtract(points[0], points[4]);
	dir = XMVector3Cross(tangent, biTangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[4].x;
	pos.y = Corners[4].y + ((Corners[7].y - Corners[4].y) / 2);
	pos.z = Corners[4].z + ((Corners[0].z - Corners[4].z) / 2);
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent));
}

void CollisionBox::updateFacePositions()
{
	XMFLOAT3 Corners[this->box.CORNER_COUNT];

	this->box.GetCorners(Corners);

	XMFLOAT3 pos;
	//BackFace
	pos.x = Corners[0].x + ((Corners[1].x - Corners[0].x) / 2);
	pos.y = Corners[0].y + ((Corners[3].y - Corners[0].y) / 2);
	pos.z = Corners[0].z;
	this->boxFaces.at(0).centerPos = pos;
	
	//FrontFace
	pos.x = Corners[4].x + ((Corners[5].x - Corners[4].x) / 2);
	pos.y = Corners[4].y + ((Corners[7].y - Corners[4].y) / 2);
	pos.z = Corners[4].z;
	this->boxFaces.at(1).centerPos = pos;
	
	//TopFace
	pos.x = Corners[7].x + ((Corners[6].x - Corners[7].x) / 2);
	pos.y = Corners[7].y;
	pos.z = Corners[7].z + ((Corners[3].z - Corners[7].z) / 2);
	this->boxFaces.at(2).centerPos = pos;
	
	//BottomFace
	pos.x = Corners[4].x + ((Corners[5].x - Corners[4].x) / 2);
	pos.y = Corners[4].y;
	pos.z = Corners[4].z + ((Corners[0].z - Corners[4].z) / 2);
	this->boxFaces.at(3).centerPos = pos;
	
	//RightFace
	pos.x = Corners[5].x;
	pos.y = Corners[5].y + ((Corners[6].y - Corners[5].y) / 2);
	pos.z = Corners[5].z + ((Corners[1].z - Corners[5].z) / 2);
	this->boxFaces.at(4).centerPos = pos;
	
	//LeftFace
	pos.x = Corners[4].x;
	pos.y = Corners[4].y + ((Corners[7].y - Corners[4].y) / 2);
	pos.z = Corners[4].z + ((Corners[0].z - Corners[4].z) / 2);
	this->boxFaces.at(5).centerPos = pos;
}
BoundingOrientedBox CollisionBox::getBoundingBox()
{
	return this->box;
}
void CollisionBox::setBoundingBox(BoundingOrientedBox boundingBox)
{

}

void CollisionBox::setPosition(XMFLOAT3 position)
{
	this->box.Center = position;
	updateFacePositions();
}
Faces CollisionBox::getFaceAt(int pos)
{
	return this->boxFaces.at(pos);
}
int CollisionBox::getFaceIndex(Faces face)
{
	for (int i = 0; i < 6; i++)
	{
		if (this->boxFaces.at(i) == face)
		{
			return i;
		}
	}
	return -1;
}
Faces CollisionBox::getClosestFace(CollisionBox* target)
{
	int faceIndex = 0;
	
	int shortestDist = sqrt((this->box.Center.x - target->boxFaces.at(faceIndex).centerPos.x) * (this->box.Center.x - target->boxFaces.at(faceIndex).centerPos.x) +
		(this->box.Center.y - target->boxFaces.at(faceIndex).centerPos.y) * (this->box.Center.y - target->boxFaces.at(faceIndex).centerPos.y) +
		(this->box.Center.z - target->boxFaces.at(faceIndex).centerPos.z) * (this->box.Center.z - target->boxFaces.at(faceIndex).centerPos.z));;
	int distance;
	for (int i = 1; i < 6; i++)
	{
		distance = sqrt((this->box.Center.x - target->boxFaces.at(i).centerPos.x) * (this->box.Center.x - target->boxFaces.at(i).centerPos.x) +
			(this->box.Center.y - target->boxFaces.at(i).centerPos.y) * (this->box.Center.y - target->boxFaces.at(i).centerPos.y) +
			(this->box.Center.z - target->boxFaces.at(i).centerPos.z) * (this->box.Center.z - target->boxFaces.at(i).centerPos.z));
		if (distance < shortestDist)
		{
			shortestDist = distance;
			faceIndex = i;
		}
	}
	return target->boxFaces.at(faceIndex);
}
