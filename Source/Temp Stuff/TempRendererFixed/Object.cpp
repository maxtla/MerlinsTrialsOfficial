#include"Object.h"

Object::Object() {

	//Shading values
	this->cDif = Vector3(0.0f, 0.0f, 0.0f);
	this->cAmbient = Vector3(0.0f, 0.0f, 0.0f);
	this->cSpec = Vector3(0.0f, 0.0f, 0.0f);
	this->cEmissive = Vector3(0.0f, 0.0f, 0.0f);
	this->specExponent = 0.0f;
	this->opacity = 0.0f;

	//Texture paths
	this->difTexPath = "";
	this->normTexPath = "";

	//Name
	this->name = "";

	//Buffers
	this->vBuffer = nullptr;
	this->iBuffer = nullptr;

	//World Matrix
	this->world = Matrix::Identity;
	this->world.CreateScale(Vector3(100, 100, 100));

	//Checks
	this->isColliding = false;
	this->isVisisble = false;

}

Object::~Object() {

	if (this->vBuffer != nullptr) {

		this->vBuffer->Release();

	}

	if (this->iBuffer != nullptr) {

		this->iBuffer->Release();

	}

}

//////////////////////MISC/////////////////////////
void Object::addVertex(Vertex newVertex) {

	this->vertices.push_back(newVertex);

}

void Object::addIndex(int newIndex) {

	this->indices.push_back(newIndex);

}

void Object::createBuffers(ID3D11Device* device) {

	//Create Vertex Buffer
	D3D11_BUFFER_DESC vBufferDesc;
	ZeroMemory(&vBufferDesc, sizeof(vBufferDesc));

	//Flags
	vBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vBufferDesc.ByteWidth = sizeof(Vertex) * this->vertexCount;
	vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBufferDesc.CPUAccessFlags = 0;
	vBufferDesc.MiscFlags = 0;

	//Data
	D3D11_SUBRESOURCE_DATA vBufferData;
	ZeroMemory(&vBufferData, sizeof(vBufferData));

	vBufferData.pSysMem = this->vertices.data();
	device->CreateBuffer(&vBufferDesc, &vBufferData, &this->vBuffer);

	//Create index buffer
	D3D11_BUFFER_DESC iBufferDesc;
	ZeroMemory(&iBufferDesc, sizeof(iBufferDesc));

	//Flags
	iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufferDesc.ByteWidth = sizeof(int) * (this->faceCount * 3);
	iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufferDesc.CPUAccessFlags = 0;
	iBufferDesc.MiscFlags = 0;

	//Data
	D3D11_SUBRESOURCE_DATA iBufferData;
	ZeroMemory(&iBufferData, sizeof(iBufferData));

	iBufferData.pSysMem = this->indices.data();
	device->CreateBuffer(&iBufferDesc, &iBufferData, &this->iBuffer);

}

void Object::writeToFile(void) {

	std::ofstream outFile;
	outFile.open("DataCheck.txt");

	outFile << this->vertexCount + "\n";
	std::string line = "";

	for (int i = 0; i < this->vertexCount; i++) {

		line += "Pos: " + std::to_string(this->vertices[i].pos.x) + ", "
			+ std::to_string(this->vertices[i].pos.y) + ", " +
			std::to_string(this->vertices[i].pos.z) + "\n";

		line += "Norm: " + std::to_string(this->vertices[i].norm.x) + ", "
			+ std::to_string(this->vertices[i].norm.y) + ", " +
			std::to_string(this->vertices[i].norm.z) + "\n";

		outFile << line;
		line = "";

	}

	outFile.close();


}

///////////////////////GET///////////////////////////
int Object::getVertexCount(void) const{

	return this->vertexCount;

}

int Object::getFaceCount(void) const{

	return this->faceCount;

}

Matrix Object::getWorld(void) const{

	return this->world;

}

ID3D11Buffer* Object::getVBuffer(void) {

	return this->vBuffer;

}

ID3D11Buffer* Object::getIBuffer(void) {

	return this->iBuffer;

}

std::vector<Object::Vertex> Object::getVertices(void) const{

	return this->vertices;

}

//////////////////////////SET////////////////////////////
void Object::setDiffuse(Vector3 dif) {

	this->cDif = dif;

}

void Object::setAmbient(Vector3 ambient) {

	this->cAmbient = ambient;

}

void Object::setSpec(Vector3 spec) {

	this->cSpec = spec;

}

void Object::setEmissive(Vector3 emissive) {

	this->cEmissive = emissive;

}

void Object::setSpecExponent(float specExponent) {

	this->specExponent = specExponent;

}

void Object::setOpacity(float opacity) {

	this->opacity = opacity;

}

void Object::setName(std::string name) {

	this->name = name;

}

void Object::setDifTexPath(std::string path) {

	this->difTexPath = path;

}

void Object::setNormTexPath(std::string path) {

	this->normTexPath = path;

}

void Object::setVertexCount(int vertices) {

	this->vertexCount = vertices;

}

void Object::setFaceCount(int faces) {

	this->faceCount = faces;

}