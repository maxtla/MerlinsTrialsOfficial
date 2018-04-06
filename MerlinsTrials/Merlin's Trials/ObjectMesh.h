#ifndef OBJECTMESH_H
#define OBJECTMESH_H
#include"SimpleMath.h"

class ObjectMesh
{
public:

	struct Vertex
	{
		DirectX::SimpleMath::Vector2 uvs;
		DirectX::SimpleMath::Vector3 normals;
		DirectX::SimpleMath::Vector3 position;
	};

	
private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
public:
	ObjectMesh();
	~ObjectMesh();
};
#endif // !OBJECTMESH_H
