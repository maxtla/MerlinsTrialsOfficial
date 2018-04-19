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

private:

	//Vertex/Index containers
	std::vector<Vertex> vertices;
	std::vector<int> indices;

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

	//Count
	int vertexCount;
	int faceCount;

	//Buffers
	ID3D11Buffer* vBuffer;
	ID3D11Buffer* iBuffer;

	//World Matrix
	Matrix world;

	//Checks
	bool isColliding;
	bool isVisisble;

public:
	
	Geometry();
	~Geometry();

	//Get
	int getVertexCount(void) const;
	int getFaceCount(void) const;
	Matrix getWorld(void) const;
	ID3D11Buffer* getVBuffer(void);
	ID3D11Buffer* getIBuffer(void);
	std::vector<Vertex> getVertices(void) const;
	std::string getName() const;
	//Set
	void setName(std::string name);
	void setSpec(Vector3 spec);
	void setAmbient(Vector3 ambient);
	void setEmissive(Vector3 emissive);
	void setDiffuse(Vector3 dif);
	void setSpecExponent(float specExponent);
	void setOpacity(float opacity);
	void setDifTexPath(std::string path);
	void setNormTexPath(std::string path);
	void setVertexCount(int vertices);
	void setFaceCount(int faces);

	//Misc
	void addVertex(Vertex newVertex);
	void addIndex(int newIndex);
	void createBuffers(ID3D11Device* device);
	void writeToFile(void);

};

#endif // !Geometry_H
