#include"Terrain.h"

Terrain::Terrain() {

	this->nrOfFaces = 0;
	this->nrOfVertices = 0;
	this->valuesPerVertex = 0;

	this->worldScale = 400.0f;
	this->worldOffset = -1500.0f;

	this->mat.wvp = DirectX::XMMatrixIdentity();
	this->mat.world = DirectX::XMMatrixIdentity();

	this->hM.height = 0;
	this->hM.width = 0;
	this->hM.vertexData = nullptr;

	this->vBuffer = nullptr;
	this->iBuffer = nullptr;
	this->cBuffer = nullptr;

	this->sampState = nullptr;

	this->grassView = nullptr;
	this->stoneView = nullptr;

}

Terrain::~Terrain() {

	if (this->hM.vertexData != nullptr) {

		for (int i = 0; i < this->hM.height; i++) {

			delete[] this->hM.vertexData[i];

		}

		delete[] this->hM.vertexData;

	}

	this->vBuffer->Release();
	this->iBuffer->Release();
	this->cBuffer->Release();

}

void Terrain::initHeightMap(ID3D11Device* device) {

	this->loadHeightMap();
	this->createBuffers(device);

}

bool Terrain::loadHeightMap() {

	bool result = true;

	FILE* file = nullptr;		//Holds current position in file
	BITMAPFILEHEADER bmHeader;	//Stores information about file
	BITMAPINFOHEADER bmInfo;	//Stores information about image
	int imageSize = 0, index = 0;
	unsigned char heightValue = ' ';

	//Open file
	fopen_s(&file, "BitMaps//BitMap16x16.bmp", "rb");	//Filepath + mode to open in (rb = Read + binary data)

	if (file == nullptr) {

		exit(-1);

	}
	else {

		//Read bitmap header/info
		fread(&bmHeader, sizeof(BITMAPFILEHEADER), 1, file);
		fread(&bmInfo, sizeof(BITMAPINFOHEADER), 1, file);

		//get width/height
		this->hM.width = bmInfo.biWidth;
		this->hM.height = bmInfo.biHeight;

		//Get size of image in bytes, stores RGB in 3 bytes
		imageSize = (this->hM.width * this->hM.height * 3);

		//init array that stores image data
		unsigned char* bmImage = new unsigned char[imageSize];

		//Set file pointer to start
		fseek(file, bmHeader.bfOffBits, SEEK_SET);

		//Store image data
		fread(bmImage, 1, imageSize, file);

		//Close file
		fclose(file);

		//Init vertexData array
		this->hM.vertexData = new DirectX::XMFLOAT3*[this->hM.height];

		for (int i = 0; i < this->hM.height; i++) {

			this->hM.vertexData[i] = new DirectX::XMFLOAT3[this->hM.width];

		}

		//Read data from greyscale image, only need value from one color channel
		int k = 0;
		float heightFactor = 50.0f;

		//Read imageData into heigthMap array
		for (int i = 0; i < hM.height; i++) {

			for (int j = 0; j < hM.width; j++) {

				heightValue = bmImage[k];		//Get heightValue(R)
				
				//Store coords
				this->hM.vertexData[i][j].x = (float)j;
				this->hM.vertexData[i][j].y = (float)heightValue / heightFactor;
				this->hM.vertexData[i][j].z = (float)i;

				//Skip ahead of the 2 other color channels(GB)
				k += 3;

			}

		}

		delete[] bmImage;
		bmImage = 0;

	}

	return result;

}

void Terrain::createBuffers(ID3D11Device* device) {

	//Vertex structure
	struct Vertex {

		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 texUV;
		DirectX::XMFLOAT3 normal;

	};
	this->valuesPerVertex = 8;

	//Set number of vertices and faces
	this->nrOfVertices = this->hM.height * this->hM.width;
	this->nrOfFaces = (this->hM.height - 1) * (this->hM.width - 1) * 2;

	//Create vector and store all vertex positions and a default normal
	std::vector<Vertex> vec(this->nrOfVertices);
	float uIndex = 0.0f;
	float vIndex = 0.0f;

	for (int i = 0; i < this->hM.height; i++) {

		for (int j = 0; j < this->hM.width; j++) {

			//Set position and temp normal
			vec[(i * this->hM.width) + j].pos = this->hM.vertexData[i][j];
			vec[(i * this->hM.width) + j].normal = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

			//Set texture coordinates
			vec[(i * this->hM.width) + j].texUV = DirectX::XMFLOAT2(uIndex, vIndex);

			//Update uIndex
			uIndex += 1.0f;

		}

		//Update u/v Index
		uIndex = 0.0f;
		vIndex += 1.0f;

	}

	//Create vector that stores all index positions
	std::vector<int> indices(this->nrOfFaces * 3);
	int k = 0;

	//Handles a quad at a time, sets index
	for (int i = 0; i < (this->hM.height - 1); i++) {

		for (int j = 0; j < (this->hM.width - 1); j++) {

			//Set indices
			indices[k] = (i * this->hM.width) + j;					//Bottom left
			indices[k + 1] = ((i + 1) * this->hM.width) + j;		//Top left
			indices[k + 2] = (i * this->hM.width) + (j + 1);		//Bottom Right

			indices[k + 3] = (i * this->hM.width) + (j + 1);		//Bottom Right
			indices[k + 4] = ((i + 1) * this->hM.width) + j;		//Top Left
			indices[k + 5] = ((i + 1) * this->hM.width) + (j + 1);	//Top Right

			//Go to next two triangles
			k += 6;

		}

	}

	//Copmute normals using normal averaging
	//Go through each vertex
	std::vector<DirectX::XMFLOAT3> tNormal;
	DirectX::XMFLOAT3 unNormalized = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	float vecX = 0.0f, vecY = 0.0f, vecZ = 0.0f;

	DirectX::XMVECTOR e1 = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR e2 = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	//Compute faceNormals
	for (int i = 0; i < this->nrOfFaces; i++) {

		//Get vector of one edge of triangle(0,2)
		vecX = vec[indices[(i * 3)]].pos.x - vec[indices[(i * 3) + 2]].pos.x;
		vecY = vec[indices[(i * 3)]].pos.y - vec[indices[(i * 3) + 2]].pos.y;
		vecZ = vec[indices[(i * 3)]].pos.z - vec[indices[(i * 3) + 2]].pos.z;
		e1 = DirectX::XMVectorSet(vecX, vecY, vecZ, 0.0f);

		//Second edge(2, 1)
		vecX = vec[indices[(i * 3) + 2]].pos.x - vec[indices[(i * 3) + 1]].pos.x;
		vecY = vec[indices[(i * 3) + 2]].pos.y - vec[indices[(i * 3) + 1]].pos.y;
		vecZ = vec[indices[(i * 3) + 2]].pos.z - vec[indices[(i * 3) + 1]].pos.z;
		e2 = DirectX::XMVectorSet(vecX, vecY, vecZ, 0.0f);

		//Cross product of the two edges gives the un normalized face normal
		DirectX::XMStoreFloat3(&unNormalized, DirectX::XMVector3Cross(e1, e2));
		tNormal.push_back(unNormalized);


	}

	//Compute vertex normals
	DirectX::XMVECTOR normalSum = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	int faceUse = 0;
	float tX = 0.0f, tY = 0.0f, tZ = 0.0f;

	for (int i = 0; i < this->nrOfVertices; i++) {

		//Check what triangle uses the vertex
		for (int j = 0; j < this->nrOfFaces; j++) {

			if (indices[(j * 3)] == i ||
				indices[(j * 3) + 1] == i ||
				indices[(j * 3) + 2] == i) {

				tX = DirectX::XMVectorGetX(normalSum) + tNormal[j].x;
				tY = DirectX::XMVectorGetY(normalSum) + tNormal[j].y;
				tZ = DirectX::XMVectorGetZ(normalSum) + tNormal[j].z;

				//If a face is using the vertex, the unnormalized face normal is added
				normalSum = DirectX::XMVectorSet(tX, tY, tZ, 0.0f);
				faceUse++;

			}

		}

		//Get normal by dividing normalSum with the number of faces sharing the vertex
		DirectX::XMVECTOR temp = { faceUse, faceUse, faceUse, faceUse };
		normalSum = DirectX::XMVectorDivide(normalSum, temp);

		//Normalize sum
		normalSum = DirectX::XMVector3Normalize(normalSum);

		//Store normal in the current vertex
		vec[i].normal.x = DirectX::XMVectorGetX(normalSum);
		vec[i].normal.y = DirectX::XMVectorGetY(normalSum);
		vec[i].normal.z = DirectX::XMVectorGetZ(normalSum);

		//Clear values
		normalSum = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		faceUse = 0;

	}

	//Create Vertex Buffer
	D3D11_BUFFER_DESC vBufferDesc;
	ZeroMemory(&vBufferDesc, sizeof(vBufferDesc));

	//Flags
	vBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vBufferDesc.ByteWidth = sizeof(Vertex) * this->nrOfVertices;
	vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBufferDesc.CPUAccessFlags = 0;
	vBufferDesc.MiscFlags = 0;

	//Data
	D3D11_SUBRESOURCE_DATA vBufferData;
	ZeroMemory(&vBufferData, sizeof(vBufferData));

	vBufferData.pSysMem = &vec[0];
	device->CreateBuffer(&vBufferDesc, &vBufferData, &this->vBuffer);

	//Create index buffer
	D3D11_BUFFER_DESC iBufferDesc;
	ZeroMemory(&iBufferDesc, sizeof(iBufferDesc));

	//Flags
	iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufferDesc.ByteWidth = sizeof(int) * (this->nrOfFaces * 3);
	iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufferDesc.CPUAccessFlags = 0;
	iBufferDesc.MiscFlags = 0;

	//Data
	D3D11_SUBRESOURCE_DATA iBufferData;
	ZeroMemory(&iBufferData, sizeof(iBufferData));

	iBufferData.pSysMem = &indices[0];
	device->CreateBuffer(&iBufferDesc, &iBufferData, &this->iBuffer);

}

void Terrain::createTexture(ID3D11Device* device) {

	//Create Grass texture view
	HRESULT hr = DirectX::CreateWICTextureFromFile(device, L"Textures//Grass.png",
		nullptr, &this->grassView);

	if (FAILED(hr)) {

		exit(-1);

	}

	//Create stone texture
	hr = DirectX::CreateWICTextureFromFile(device, L"Textures//Stone.png",
		nullptr, &this->stoneView);

	if (FAILED(hr)) {

		exit(-1);

	}

}

void Terrain::createConstBuffer(ID3D11Device* device) {

	HRESULT hr = 0;

	//Buffer desc
	D3D11_BUFFER_DESC constBufferDesc;
	constBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constBufferDesc.ByteWidth = sizeof(Matrix);
	constBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constBufferDesc.MiscFlags = 0;
	constBufferDesc.StructureByteStride = 0;

	//Check if failed
	hr = device->CreateBuffer(&constBufferDesc, nullptr, &this->cBuffer);

	if (FAILED(hr)) {

		exit(-1);

	}

}

void Terrain::updateMatrixValues(DirectX::XMMATRIX view, DirectX::XMMATRIX proj,
	int wWidth, int wHeight) {

	//World offset pos by -1500 and scale by 400x
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	world = DirectX::XMMatrixScaling(this->worldScale, this->worldScale, this->worldScale)
		*  DirectX::XMMatrixTranslation(this->worldOffset, this->worldOffset, this->worldOffset);
	mat.world = world;

	//World * View * Projection Matrix
	mat.wvp = DirectX::XMMatrixTranspose(world * view * proj);

}

void Terrain::mapConstBuffer(ID3D11DeviceContext* dContext) {

	//Map buffer
	D3D11_MAPPED_SUBRESOURCE dataPtr;
	dContext->Map(this->cBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &dataPtr);
	memcpy(dataPtr.pData, &this->mat, sizeof(Matrix));
	dContext->Unmap(this->cBuffer, 0);

	//Set rescources to shaders
	dContext->GSSetConstantBuffers(0, 1, &this->cBuffer);

}

ID3D11ShaderResourceView* Terrain::getGrassView(void) {

	return this->grassView;

}

ID3D11ShaderResourceView* Terrain::getStoneView(void) {

	return this->stoneView;

}

int Terrain::getNrOfFaces(void) const {

	return this->nrOfFaces;

}

int Terrain::getNrOfVertices(void) const {

	return this->nrOfVertices;

}

int Terrain::getValuesPerVertex(void) const {

	return this->valuesPerVertex;

}

ID3D11Buffer* Terrain::getVertexBuffer() {

	return this->vBuffer;

}

ID3D11Buffer* Terrain::getIndexBuffer() {

	return this->iBuffer;

}

float Terrain::getHeightValueAtPos(float x, float z) const {

	float height = 0.0f;
	bool stop = false;

	//check bounds of terrain
	if (x > this->worldOffset && x < (this->hM.width * this->worldScale) + this->worldOffset &&
		z > this->worldOffset && z < (this->hM.height * this->worldScale) + this->worldOffset) {

		//Find a near vertex point
		int xIndex = (std::abs(this->worldOffset - x)) / this->worldScale;
		int zIndex = (std::abs(this->worldOffset - z)) / this->worldScale;

		//Take 4 close points average
		float h1 = (this->hM.vertexData[zIndex][xIndex].y * this->worldScale) + this->worldOffset;
		float h2 = 0.0f;
		float h3 = 0.0f;
		float h4 = 0.0f;
		float count = 1.0f;

		if (zIndex < (this->hM.height - 1)) {

			h2 = (this->hM.vertexData[zIndex + 1][xIndex].y * this->worldScale) + this->worldOffset;
			count++;

		}

		if (xIndex < (this->hM.width - 1)) {

			h3 = (this->hM.vertexData[zIndex][xIndex + 1].y * this->worldScale) + this->worldOffset;
			count++;

		}

		if (zIndex < (this->hM.height - 1) && xIndex < (this->hM.width - 1)) {

			h4 = (this->hM.vertexData[zIndex + 1][xIndex + 1].y * this->worldScale) + this->worldOffset;
			count++;

		}

		height = (h1 + h2 + h3 + h4) / count;

	}

	return height;

}

void Terrain::createSamplerState(ID3D11Device* device) {

	//Create Desc
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));

	//Flags
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.MaxAnisotropy = 1;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//Create samplerState
	device->CreateSamplerState(&sampDesc, &this->sampState);

}

ID3D11SamplerState* Terrain::getSamplerState() {

	return this->sampState;

}