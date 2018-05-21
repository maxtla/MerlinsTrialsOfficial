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
	this->generateFaces();
}
CollisionBox::CollisionBox(BoundingOrientedBox boundingBox)
{
	this->box = BoundingOrientedBox(boundingBox);
	if (boundingBox.Orientation.x == 0 && boundingBox.Orientation.y == 0 && boundingBox.Orientation.z == 0 && boundingBox.Orientation.w == 0)
	{
		XMStoreFloat4(&this->box.Orientation, XMQuaternionRotationMatrix(XMMatrixRotationY(0)));
	}
	this->generateFaces();
}

CollisionBox::CollisionBox(XMFLOAT3 *points, int size)
{
	BoundingOrientedBox object;
	object.CreateFromPoints(object, size, points,sizeof(XMFLOAT3));
	this->box = object;
	this->generateFaces();
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

	//BackFace 0
	XMVECTOR biTangent, tangent, dir;
	biTangent = XMVectorSubtract(points[3], points[0]);
	tangent = XMVectorSubtract(points[1], points[0]);
	dir = XMVector3Cross(tangent, biTangent);
	dir = XMVector3Normalize(dir);
	XMFLOAT3 pos;
	pos.x = Corners[0].x + ((Corners[1].x - Corners[0].x) / 2);
	pos.y = Corners[0].y + ((Corners[3].y - Corners[0].y) / 2);
	pos.z = Corners[0].z;
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent,XMFLOAT3(0,1,3)));
	//FrontFace 1
	biTangent = XMVectorSubtract(points[7], points[4]);
	tangent = XMVectorSubtract(points[5], points[4]);
	dir = XMVector3Cross(biTangent, tangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[4].x + ((Corners[5].x - Corners[4].x) / 2);
	pos.y = Corners[4].y + ((Corners[7].y - Corners[4].y) / 2);
	pos.z = Corners[4].z;
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent, XMFLOAT3(7,4,5)));

	//TopFace 2
	biTangent = XMVectorSubtract(points[3], points[7]);
	tangent = XMVectorSubtract(points[6], points[7]);
	dir = XMVector3Cross(biTangent, tangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[7].x + ((Corners[6].x - Corners[7].x) / 2);
	pos.y = Corners[7].y;
	pos.z = Corners[7].z + ((Corners[3].z - Corners[7].z) / 2);
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent, XMFLOAT3(7,6,3)));
	//BottomFace 3
	biTangent = XMVectorSubtract(points[0], points[4]);
	tangent = XMVectorSubtract(points[5], points[4]);
	dir = XMVector3Cross(tangent, biTangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[4].x + ((Corners[5].x - Corners[4].x) / 2);
	pos.y = Corners[4].y;
	pos.z = Corners[4].z + ((Corners[0].z - Corners[4].z) / 2);
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent, XMFLOAT3(0,4,5)));

	//RightFace 4
	biTangent = XMVectorSubtract(points[6], points[5]);
	tangent = XMVectorSubtract(points[1], points[5]);
	dir = XMVector3Cross(biTangent, tangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[5].x;
	pos.y = Corners[5].y + ((Corners[6].y - Corners[5].y) / 2);
	pos.z = Corners[5].z + ((Corners[1].z - Corners[5].z) / 2);
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent, XMFLOAT3(6,5,1)));
	//LeftFace 5
	biTangent = XMVectorSubtract(points[7], points[4]);
	tangent = XMVectorSubtract(points[0], points[4]);
	dir = XMVector3Cross(tangent, biTangent);
	dir = XMVector3Normalize(dir);
	pos.x = Corners[4].x;
	pos.y = Corners[4].y + ((Corners[7].y - Corners[4].y) / 2);
	pos.z = Corners[4].z + ((Corners[0].z - Corners[4].z) / 2);
	this->boxFaces.push_back(Faces(dir, pos, biTangent, tangent, XMFLOAT3(7,0,4)));
}

void CollisionBox::updateFacePositions()
{
	XMFLOAT3 Corners[this->box.CORNER_COUNT];

	this->box.GetCorners(Corners);

	XMFLOAT3 pos;
	//BackFace 0
	pos.x = Corners[0].x + ((Corners[1].x - Corners[0].x) / 2);
	pos.y = Corners[0].y + ((Corners[3].y - Corners[0].y) / 2);
	pos.z = Corners[0].z;
	this->boxFaces.at(0).centerPos = pos;
	
	//FrontFace 1
	pos.x = Corners[4].x + ((Corners[5].x - Corners[4].x) / 2);
	pos.y = Corners[4].y + ((Corners[7].y - Corners[4].y) / 2);
	pos.z = Corners[4].z;
	this->boxFaces.at(1).centerPos = pos;
	
	//TopFace 2
	pos.x = Corners[7].x + ((Corners[6].x - Corners[7].x) / 2);
	pos.y = Corners[7].y;
	pos.z = Corners[7].z + ((Corners[3].z - Corners[7].z) / 2);
	this->boxFaces.at(2).centerPos = pos;
	
	//BottomFace 3
	pos.x = Corners[4].x + ((Corners[5].x - Corners[4].x) / 2);
	pos.y = Corners[4].y;
	pos.z = Corners[4].z + ((Corners[0].z - Corners[4].z) / 2);
	this->boxFaces.at(3).centerPos = pos;
	
	//RightFace 4
	pos.x = Corners[5].x;
	pos.y = Corners[5].y + ((Corners[6].y - Corners[5].y) / 2);
	pos.z = Corners[5].z + ((Corners[1].z - Corners[5].z) / 2);
	this->boxFaces.at(4).centerPos = pos;
	
	//LeftFace 5
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

Faces CollisionBox::getFace(XMVECTOR normal)
{
	int pos = 0;
	bool found = 0;
	for (int i = 0; i < 6 && !found; i++)
	{
		if (XMVectorGetX(XMVectorEqual(this->boxFaces.at(i).normal, normal)))
		{
			pos = i;
			found = true;
		}
	}
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
int CollisionBox::getClosestFace(CollisionBox* target) //Only front, back, left and right sides works.
{
	int faceIndex = 0;
	int distance;
	std::vector<XMVECTOR> planes;
	XMVECTOR intersection;
	int shortestDist = INFINITY;
	std::vector<int> distances;

	for (auto face : this->boxFaces)
	{
		planes.push_back(DirectX::XMPlaneFromPointNormal(XMLoadFloat3(&face.centerPos), face.normal));
	}
	int s = 0;
	float val1 = INFINITY;
	float val2 = INFINITY;
	for (auto plane : planes)
	{
		intersection = XMPlaneIntersectLine(plane, XMLoadFloat3(&this->box.Center), XMLoadFloat3(&target->box.Center));
		if (val1 == INFINITY && s != 2 && s != 3)
		{
			distances.push_back(XMVectorGetX(XMVector3Length(XMVectorSubtract(intersection, XMLoadFloat3(&this->box.Center)))));
			 val1 = XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&target->box.Center), XMLoadFloat3(&this->box.Center))), plane));
		}
		else if(s != 2 && s != 3)
		{
			val2 = XMVectorGetX(XMVector3AngleBetweenVectors(XMVector3Normalize(XMVectorSubtract(XMLoadFloat3(&target->box.Center), XMLoadFloat3(&this->box.Center))), plane));
			if (val2 < val1)
			{
				distances.push_back(XMVectorGetX(XMVector3Length(XMVectorSubtract(intersection, XMLoadFloat3(&this->box.Center)))));
				if(s > 3)
				distances.at(s - 3) = -1;
				else
				distances.at(s - 1) = -1;
			}
			else
			{
				distances.push_back(-1);
			}
			val1 = INFINITY;
			val2 = INFINITY;
			
		}
		s++;
	}
	shortestDist = distances.at(0);
	for (int d = 1; d < distances.size(); d++)
	{
		if (distances.at(d) != -1)
		{
			if (distances.at(d) < shortestDist || shortestDist == -1)
			{
				shortestDist = distances.at(d);
				faceIndex = d;
			}
		}
	}
	
	int firstSide = -1;
	int secondSide = -1;
	for (int d = 1; d < distances.size(); d++)
	{
		if(d != faceIndex)
		{
			if (distances.at(d) == shortestDist)
			{
				if (firstSide != -1)
				{
					secondSide = d;
				}
				else
				{
					firstSide = d;
				}
			}
		}

	}
	XMFLOAT3 intersection1;
	XMFLOAT3 intersection2;

		if (firstSide != -1)
		{

			XMStoreFloat3(&intersection1, XMVector3Length(XMPlaneIntersectLine(planes.at(faceIndex), XMLoadFloat3(&this->box.Center), XMLoadFloat3(&target->box.Center))));
			XMStoreFloat3(&intersection2, XMVector3Length(XMPlaneIntersectLine(planes.at(firstSide), XMLoadFloat3(&this->box.Center), XMLoadFloat3(&target->box.Center))));
			if (intersection2.x < intersection1.x)
			{
				faceIndex = firstSide;
				intersection1 = intersection2;

			}
		}
		if (secondSide != -1)
		{
			XMStoreFloat3(&intersection1, XMVector3Length(XMPlaneIntersectLine(planes.at(faceIndex), XMLoadFloat3(&this->box.Center), XMLoadFloat3(&target->box.Center))));
			XMStoreFloat3(&intersection2, XMVector3Length(XMPlaneIntersectLine(planes.at(secondSide), XMLoadFloat3(&this->box.Center), XMLoadFloat3(&target->box.Center))));
			if (intersection2.x < intersection1.x)
			{
				faceIndex = secondSide;
			}
		}

	if (faceIndex >= 2)
	{
		faceIndex += 2;
	}
	
	return faceIndex;
}

//Faces CollisionBox::getClosestFace(XMFLOAT3 target)
//{
//	int faceIndex = 0;
//
//	int shortestDist = sqrt((target.x - this->boxFaces.at(faceIndex).centerPos.x) * (target.x - this->boxFaces.at(faceIndex).centerPos.x) +
//		(target.y - this->boxFaces.at(faceIndex).centerPos.y) * (target.y - this->boxFaces.at(faceIndex).centerPos.y) +
//		(target.z - this->boxFaces.at(faceIndex).centerPos.z) * (target.z - this->boxFaces.at(faceIndex).centerPos.z));
//	int distance;
//	for (int i = 1; i < 6; i++)
//	{
//		distance = sqrt((target.x - this->boxFaces.at(i).centerPos.x) * (target.x - this->boxFaces.at(i).centerPos.x) +
//			(target.y - this->boxFaces.at(i).centerPos.y) * (target.y - this->boxFaces.at(i).centerPos.y) +
//			(target.z - this->boxFaces.at(i).centerPos.z) * (target.z - this->boxFaces.at(i).centerPos.z));
//		if (distance < shortestDist)
//		{
//			shortestDist = distance;
//			faceIndex = i;
//		}
//	}
//	return this->boxFaces.at(faceIndex);
//}
//
//Faces CollisionBox::getClosestFace(Faces target)
//{
//	int faceIndex = 0;
//
//	int shortestDist = sqrt((target.centerPos.x - this->boxFaces.at(faceIndex).centerPos.x) * (target.centerPos.x - this->boxFaces.at(faceIndex).centerPos.x) +
//		(target.centerPos.y - this->boxFaces.at(faceIndex).centerPos.y) * (target.centerPos.y - this->boxFaces.at(faceIndex).centerPos.y) +
//		(target.centerPos.z - this->boxFaces.at(faceIndex).centerPos.z) * (target.centerPos.z - this->boxFaces.at(faceIndex).centerPos.z));
//	int distance;
//	for (int i = 1; i < 6; i++)
//	{
//		distance = sqrt((target.centerPos.x - this->boxFaces.at(i).centerPos.x) * (target.centerPos.x - this->boxFaces.at(i).centerPos.x) +
//			(target.centerPos.y - this->boxFaces.at(i).centerPos.y) * (target.centerPos.y - this->boxFaces.at(i).centerPos.y) +
//			(target.centerPos.z - this->boxFaces.at(i).centerPos.z) * (target.centerPos.z - this->boxFaces.at(i).centerPos.z));
//		if (distance < shortestDist)
//		{
//			shortestDist = distance;
//			faceIndex = i;
//		}
//
//	}
//	
//
//	return this->boxFaces.at(faceIndex);
//}

CollisionBox CollisionBox::getWorldBox(XMMATRIX world)
{
	
	XMFLOAT3 Corners[this->box.CORNER_COUNT];
	this->box.GetCorners(Corners);
	XMVECTOR points;
	for (int i = 0; i < this->box.CORNER_COUNT; i++)
	{
		points = XMLoadFloat3(&Corners[i]);
		XMVector3TransformCoord(points, world);
		XMStoreFloat3(&Corners[i], points);
	}
	CollisionBox worldBox = CollisionBox(Corners, this->box.CORNER_COUNT);
	return worldBox;
}

std::vector<Faces> CollisionBox::getBoxFaces()
{
	return this->boxFaces;
}

XMFLOAT3 CollisionBox::getSupportVertex(XMVECTOR normal)
{
	std::vector<XMFLOAT3> SupportPoints;
	XMFLOAT3 Corners[this->box.CORNER_COUNT];
	XMVECTOR point;
	float distance = { -INFINITY };
	float newDistance = 0;
	this->box.GetCorners(Corners);

	int indexPos = { 0 };
	for (int i = 0; i < this->box.CORNER_COUNT; i++)
	{
		
		newDistance = XMVectorGetX(XMVector3Dot(XMLoadFloat3(&Corners[i]), normal));
		if (newDistance > distance)
		{
			distance = newDistance;
			indexPos = i;
		}
	
	}
	return Corners[indexPos];
}

XMVECTOR CollisionBox::getSupportNormal(XMVECTOR normal)
{
	std::vector<XMFLOAT3> SupportPoints;
	XMFLOAT3 Corners[this->box.CORNER_COUNT];
	XMVECTOR point;
	float distance[3] = { -INFINITY };
	float newDistance = 0;
	this->box.GetCorners(Corners);
	int indexPos[3] = { 0 };
	for (int i = 0; i < this->box.CORNER_COUNT; i++)
	{

		newDistance = XMVectorGetX(XMVector3Dot(XMLoadFloat3(&Corners[i]), normal));
		for (int k = 0; k < 3; k++)
		{
			if (newDistance > distance[k])
			{
				distance[k] = newDistance;
				indexPos[k] = i;
				k = 3;
			}
			else
			{
				bool dur = 0;
			}
		}

	}
	XMVECTOR points[8];
	for (int i = 0; i < this->box.CORNER_COUNT; i++)
	{
		points[i] = XMLoadFloat3(&Corners[i]);
	}
	XMVECTOR biTangent, tangent, dir;
	biTangent = XMVectorSubtract(points[indexPos[1]], points[indexPos[0]]);
	tangent = XMVectorSubtract(points[indexPos[2]], points[indexPos[0]]);
	dir = XMVector3Cross(tangent, biTangent);
	dir = XMVector3Normalize(dir);
	return dir;
}

int CollisionBox::getOppositeFaceIndex(int FaceIndex)
{
	if (FaceIndex == 1 || FaceIndex == 3 || FaceIndex == 5)
	{
		return (FaceIndex - 1);
	}
	else
	{
		return (FaceIndex + 1);
	}
}