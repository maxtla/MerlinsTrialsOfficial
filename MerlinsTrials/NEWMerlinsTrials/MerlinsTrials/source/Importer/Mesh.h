#ifndef OBJECT_H
#define OBJECT_H

#include<d3d11.h>
#include<SimpleMath.h>
#include<VertexTypes.h>
#include<vector>
#include<string>
#include<fstream>
#include<GeometricPrimitive.h>
#include<PrimitiveBatch.h>
#include<WICTextureLoader.h>

#include "..\Shaders\BasicShader.h"
#include "..\Shaders\NormalMapShader.h"
#include "..\Helpers\DebugDraw.h"


#define PATH_BUFFER_SIZE 1024

enum BOUNDINGTYPE
{
	OBB = 0,
	SPHERE = 1,
	AABB = 2,
	TERRAIN = 3,
	NONE = 4
};

using namespace DirectX::SimpleMath;

class Mesh {

public:
	Mesh(const Mesh&m){}

	//has booleans
	bool hasPos = false;
	bool hasPosCol = false;
	bool hasPosTex = false;
	bool hasPosNor = false;
	bool hasPosNorCol = false;
	bool hasPosNorTex = false;
	bool hasPosColTex = false;
	bool hasPosNorColTex = false;
	bool hasPosNorTanColTex = false;
	//has textures
	bool hasDiffuseTexture = false;
	bool hasNormalTexture = false;
	bool hasSpecularTexture = false;
	//has for boundingbox etc.
	bool hasAABB = false;
	bool hasSphere = false;
	bool hasOBB = false;
	bool isTerrain = false;
	bool hasNoBoundingShape = false;

	//Different kind of containers depending on VertexType (only one is filled per mesh)
	std::vector<DirectX::VertexPosition> vertices_P;
	std::vector<DirectX::VertexPositionColor> vertices_PC;
	std::vector<DirectX::VertexPositionTexture> vertices_PT;
	std::vector<DirectX::VertexPositionNormal> vertices_PN;
	std::vector<DirectX::VertexPositionNormalColor> vertices_PNC;
	std::vector<DirectX::VertexPositionNormalTexture> vertices_PNT; //most commonly used
	std::vector<DirectX::VertexPositionColorTexture> vertices_PCT;
	std::vector<DirectX::VertexPositionNormalColorTexture> vertices_PNCT;
	std::vector<DirectX::VertexPositionNormalTangentColorTexture> vertices_PNTCT;

	//index data
	std::vector<uint16_t> indices;

	//public bounding shapes
	BoundingBox m_AABB;
	BoundingSphere m_Sphere;
	BoundingOrientedBox m_OBB;
protected:
	//textures
	ID3D11Resource * m_DiffuseTexture = nullptr;
	ID3D11ShaderResourceView * m_DiffuseTextureView = nullptr;
	ID3D11Resource * m_NormalTexture = nullptr;
	ID3D11ShaderResourceView * m_NormalTextureView = nullptr;
	ID3D11Resource * m_SpecularTexture = nullptr;
	ID3D11ShaderResourceView * m_SpecularTextureView = nullptr;

	//Shading values
	Vector3 cDif;
	Vector3 cAmbient;
	Vector3 cSpec;
	Vector3 cEmissive;
	float specExponent;
	float opacity;

	//Texture paths
	std::string difTexPath = "";
	std::string normTexPath = "";
	std::string specTexPath = "";

	//Object name
	std::string name;

	//Count
	int vertexCount;
	int faceCount;

	//Buffers
	ID3D11Buffer* vBuffer = nullptr;
	ID3D11Buffer* iBuffer = nullptr;

	//helper methods
	void getByteWidth(D3D11_BUFFER_DESC &vBufferDesc);
	void getVertexData(D3D11_SUBRESOURCE_DATA &vBufferData);
public:
	
	Mesh();
	~Mesh();

	//Common Get
	int getVertexCount() const { return vertexCount; }
	int getFaceCount() const { return faceCount; }
	ID3D11Buffer** getVBuffer() { return &vBuffer; }
	ID3D11Buffer* getIBuffer() { return iBuffer; }
	std::string getName() const { return name; }
	UINT getStride() const;
	size_t getNrOfIndices() const { return indices.size(); }

	//material get 
	Vector3 getSpec() const { return this->cSpec; }
	Vector3 getDif() const { return this->cDif; }
	Vector3 getEmissive() const { return this->cEmissive; }
	Vector3 getAmbient() const { return this->cAmbient; }
	float getSpecExponent() const { return this->specExponent; }
	float getOpaciy() const { return this->opacity; }
	std::vector<Vector3> getTerrainPoints();
	std::vector<XMFLOAT3> getAllPositions();

	//packed color vectors
	Vector4 getSpec4() const { return Vector4(cSpec.x, cSpec.y, cSpec.z, specExponent); }
	Vector4 getDif4() const { return Vector4(cDif.x, cDif.y, cDif.z, opacity); }
	Vector4 getEmissive4() const { return Vector4(cEmissive.x, cEmissive.y, cEmissive.z, opacity); }
	Vector4 getAmbient4() const { return Vector4(cAmbient.x, cAmbient.y, cAmbient.z, opacity); }

	//Set
	void setName(std::string name) { this->name = name; }
	void setSpec(Vector3 spec) { this->cSpec = spec; }
	void setAmbient(Vector3 ambient) { this->cAmbient = ambient; }
	void setEmissive(Vector3 emissive) { this->cEmissive = emissive; }
	void setDiffuse(Vector3 dif) { this->cDif = dif; }
	void setSpecExponent(float specExp) { this->specExponent = specExp; }
	void setOpacity(float opacity) { this->opacity = opacity; }
	void setDifTexPath(std::string path) { this->difTexPath = path; }
	void setNormTexPath(std::string path) { this->normTexPath = path; }
	void setSpecTexPath(std::string path) { this->specTexPath = path; }
	void setVertexCount(int count) { this->vertexCount = count; }
	void setFaceCount(int count) { this->faceCount = count; }

	//Create methods
	void createBuffers(ID3D11Device* device);
	void createDiffuseSRV(ID3D11Device * pDev, std::string modelPath);
	void createNormalSRV(ID3D11Device * pDev, std::string modelPath);
	void createSpecularSRV(ID3D11Device * pDev, std::string modelPath);
	void createBoundingShapeFromPoints(int type, float scaling, const XMFLOAT3 * arrPtr, size_t nrOf, size_t stride);
	void createBoungingShapeFromType(int type, float scaling = 1.0f);
	//we need a Draw functions for each different Shader class we own
	//ATM we only need a common draw function for the BasicShader
	void Draw(BasicShader * pShader);
	void Draw(NormalMapShader * pShader);
	void DrawDebugMode(PrimitiveBatch<DirectX::VertexPositionColor> *batch, Vector4 color);
	//The update function updates the BOB's orientation / scaling etc.
	void Update(Matrix transformation);
};

#endif // !OBJECT_H
