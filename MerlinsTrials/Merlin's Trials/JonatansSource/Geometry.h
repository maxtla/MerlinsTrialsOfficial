#ifndef GEOMETRY_H
#define GEOMETRY_H

#include<d3d11.h>
#include<SimpleMath.h>
#include<vector>
#include<string>
#include<fstream>

using namespace DirectX::SimpleMath;

class Geometry {

public:

	//Vertex struct
	struct Vertex {

		Vector3 pos;
		Vector3 norm;

	};

	//Vertex/Index containers
	std::vector<Vertex> vertices;
	std::vector<int> indices;

private:



	//Shading values
	Vector3 cDif;
	Vector3 cAmbient;
	Vector3 cSpec;
	Vector3 cEmissive;
	float specExponent;
	float opacity;

	//Texture paths
	std::string difTexPath;
	std::string normTexPath;

	//Geometry name
	std::string meshName;

	int vertexCount;
	int faceCount;

	//Checks
	bool isColliding;
	bool isVisisble;

public:
	
	Geometry();
	~Geometry();

	//Get
	int getVertexCount() const;
	int getFaceCount() const;
	std::string getName() const;
	//Set
	void setName(const std::string &name);
	void setSpec(const Vector3 &spec);
	void setAmbient(const Vector3 &ambient);
	void setEmissive(const Vector3 &emissive);
	void setDiffuse(const Vector3 &dif);
	void setSpecExponent(const float &specExponent);
	void setOpacity(const float &opacity);
	void setDifTexPath(const std::string &path);
	void setNormTexPath(const std::string &path);
	void setVertexCount(const unsigned int &in_count);
	void setFaceCount(const unsigned int &in_count);
	//Misc
	void addVertex(Vertex newVertex);
	void addIndex(int newIndex);


};

#endif // !Geometry_H
