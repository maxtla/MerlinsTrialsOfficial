#ifndef OBJECT_H
#define OBJECT_H

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
	std::vector<Vertex> vertices_PN;
	std::vector<DirectX::VertexPositionNormalTexture> vertices_PNT; //PNT stands for Position normal texture
	std::vector<int> indices;
protected:


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

	//Object name
	std::string name;

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
	bool hasPosNormUV = false;

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
	std::vector<int> getIndices(void) const;
	std::string getName(void) const;

	Vector3 getSpec(void) const;
	Vector3 getDif(void) const;
	Vector3 getEmissive(void) const;
	float getSpecExponent(void) const;
	float getOpaciy(void) const;

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

#endif // !OBJECT_H
