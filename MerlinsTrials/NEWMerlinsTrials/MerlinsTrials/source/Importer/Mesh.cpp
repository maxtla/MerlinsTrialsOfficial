#include "stdafx.h"
#include"Mesh.h"

Mesh::Mesh() {

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

}

Mesh::~Mesh() {

	
	if (vBuffer)
		vBuffer->Release();
	if (iBuffer)
		iBuffer->Release();
	if (m_DiffuseTexture)
		m_DiffuseTexture->Release();
	if (m_DiffuseTextureView)
		m_DiffuseTextureView->Release();
	if (m_NormalTexture)
		m_NormalTexture->Release();
	if (m_NormalTextureView)
		m_NormalTextureView->Release();
	if (m_SpecularTexture)
		m_SpecularTexture->Release();
	if (m_SpecularTextureView)
		m_SpecularTextureView->Release();

	indices.clear();

	vertices_P.clear();
	vertices_PC.clear();
	vertices_PT.clear();
	vertices_PN.clear();
	vertices_PNC.clear();
	vertices_PNT.clear();
	vertices_PCT.clear();
	vertices_PNCT.clear();
	vertices_PNTCT.clear();

}

void Mesh::getVertexData(D3D11_SUBRESOURCE_DATA &vBufferData)
{
	if (hasPos)
	{
		vBufferData.pSysMem = vertices_P.data();
		return;
	}
	else if (hasPosCol)
	{
		vBufferData.pSysMem = vertices_PC.data();
		return;
	}
	else if (hasPosTex)
	{
		vBufferData.pSysMem = vertices_PT.data();
		return;
	}
	else if (hasPosNor)
	{
		vBufferData.pSysMem = vertices_PN.data();
		return;
	}
	else if (hasPosNorCol)
	{
		vBufferData.pSysMem = vertices_PNC.data();
		return;
	}
	else if (hasPosNorTex)
	{
		vBufferData.pSysMem = vertices_PNT.data();
		return;
	}
	else if (hasPosColTex)
	{
		vBufferData.pSysMem = vertices_PCT.data();
		return;
	}
	else if (hasPosNorColTex)
	{
		vBufferData.pSysMem = vertices_PNCT.data();
		return;
	}
	else if (hasPosNorTanColTex)
	{
		vBufferData.pSysMem = vertices_PNTCT.data();
		return;
	}
	else
		return;
}

void Mesh::getByteWidth(D3D11_BUFFER_DESC &vBufferDesc)
{
	if (hasPos)
	{
		vBufferDesc.ByteWidth = sizeof(DirectX::VertexPosition) * vertices_P.size();
		return;
	}
	else if (hasPosCol)
	{
		vBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionColor) * vertices_PC.size();
		return;
	}
	else if (hasPosTex)
	{
		vBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionTexture) * vertices_PT.size();
		return;
	}
	else if (hasPosNor)
	{
		vBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionNormal) * vertices_PN.size();
		return;
	}
	else if (hasPosNorCol)
	{
		vBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionNormalColor) * vertices_PNC.size();
		return;
	}
	else if (hasPosNorTex)
	{
		vBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionNormalTexture) * vertices_PNT.size();
		return;
	}
	else if (hasPosColTex)
	{
		vBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionColorTexture) * vertices_PCT.size();
		return;
	}
	else if (hasPosNorColTex)
	{
		vBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionNormalColorTexture) * vertices_PNCT.size();
		return;
	}
	else if (hasPosNorTanColTex)
	{
		vBufferDesc.ByteWidth = sizeof(DirectX::VertexPositionNormalTangentColorTexture) * vertices_PNTCT.size();
		return;
	}
	else
		return;

}

void Mesh::createBuffers(ID3D11Device* device) {

	//Create Vertex Buffer
	D3D11_BUFFER_DESC vBufferDesc;
	ZeroMemory(&vBufferDesc, sizeof(vBufferDesc));

	//Flags
	vBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vBufferDesc.CPUAccessFlags = 0;
	vBufferDesc.MiscFlags = 0;
	getByteWidth(vBufferDesc);

	//Data
	D3D11_SUBRESOURCE_DATA vBufferData;
	ZeroMemory(&vBufferData, sizeof(vBufferData));

	getVertexData(vBufferData);
	device->CreateBuffer(&vBufferDesc, &vBufferData, &this->vBuffer);

	//Create index buffer
	D3D11_BUFFER_DESC iBufferDesc;
	ZeroMemory(&iBufferDesc, sizeof(iBufferDesc));

	//Flags
	iBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	iBufferDesc.ByteWidth = sizeof(uint16_t) * this->indices.size();
	iBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	iBufferDesc.CPUAccessFlags = 0;
	iBufferDesc.MiscFlags = 0;

	//Data
	D3D11_SUBRESOURCE_DATA iBufferData;
	ZeroMemory(&iBufferData, sizeof(iBufferData));
	iBufferData.pSysMem = this->indices.data();

	device->CreateBuffer(&iBufferDesc, &iBufferData, &this->iBuffer);
}


UINT Mesh::getStride() const
{
	UINT stride = 0;
	if (hasPos)
		stride = sizeof(DirectX::VertexPosition);
	else if (hasPosCol)
		stride = sizeof(DirectX::VertexPositionColor);
	else if (hasPosTex)
		stride = sizeof(DirectX::VertexPositionTexture);
	else if (hasPosNor)
		stride = sizeof(DirectX::VertexPositionNormal);
	else if (hasPosNorCol)
		stride = sizeof(DirectX::VertexPositionNormalColor);
	else if (hasPosNorTex)
		stride = sizeof(DirectX::VertexPositionNormalTexture);
	else if (hasPosColTex)
		stride = sizeof(DirectX::VertexPositionColorTexture);
	else if (hasPosNorColTex)
		stride = sizeof(DirectX::VertexPositionNormalColorTexture);
	else if (hasPosNorTanColTex)
		stride = sizeof(DirectX::VertexPositionNormalTangentColorTexture);

	return stride;
}
////////////////////////////MISC////////////////////////////

void Mesh::Draw(BasicShader * pShader)
{
	pShader->m_effect->SetDiffuseColor(this->cDif);
	pShader->m_effect->SetAmbientLightColor(this->cAmbient);
	pShader->m_effect->SetEmissiveColor(this->cEmissive);
	pShader->m_effect->SetSpecularColor(this->cSpec);
	pShader->m_effect->SetSpecularPower(this->specExponent);
	//pShader->m_effect->SetAlpha(this->opacity);
	pShader->m_effect->SetTexture(this->m_DiffuseTextureView);
	

	pShader->Apply();

	pShader->gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pShader->gDeviceContext->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R16_UINT, 0);
	UINT stride = getStride();
	UINT offset = 0;
	pShader->gDeviceContext->IASetVertexBuffers(0, 1, &this->vBuffer, &stride, &offset);

	pShader->gDeviceContext->DrawIndexed(indices.size(), 0, 0);
}

void Mesh::Draw(NormalMapShader * pShader)
{
	pShader->m_effect->SetDiffuseColor(this->cDif);
	pShader->m_effect->SetAmbientLightColor(this->cAmbient);
	pShader->m_effect->SetEmissiveColor(this->cEmissive);
	pShader->m_effect->SetSpecularColor(this->cSpec);
	pShader->m_effect->SetSpecularPower(this->specExponent);
	pShader->m_effect->SetAlpha(this->opacity);

	if (hasDiffuseTexture)
		pShader->m_effect->SetTexture(this->m_DiffuseTextureView);
	if (hasNormalTexture)
		pShader->m_effect->SetNormalTexture(this->m_NormalTextureView);
	if (hasSpecularTexture)
		pShader->m_effect->SetSpecularTexture(this->m_SpecularTextureView);

	pShader->Apply();

	pShader->gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pShader->gDeviceContext->IASetIndexBuffer(iBuffer, DXGI_FORMAT_R16_UINT, 0);
	UINT stride = getStride();
	UINT offset = 0;
	pShader->gDeviceContext->IASetVertexBuffers(0, 1, &this->vBuffer, &stride, &offset);

	pShader->gDeviceContext->DrawIndexed(indices.size(), 0, 0);
}

void Mesh::DrawDebugMode(PrimitiveBatch<VertexPositionColor> *batch, Vector4 color)
{
	batch->Begin();
	if (!hasNoBoundingShape)
	{
		if (hasOBB)
			DebugDraw::Draw(batch, m_OBB, color);
		else if (hasSphere)
			DebugDraw::Draw(batch, m_Sphere, color);
		else if (hasAABB)
			DebugDraw::Draw(batch, m_AABB, color);
	}
	batch->End();
}

void Mesh::createDiffuseSRV(ID3D11Device * pDev, std::string modelPath)
{
	//less than 4 because a texture path needs atleast this p.ext - which are 5 chars minimum
	if (difTexPath.length() < 4)
		throw(std::runtime_error("ERROR: Unable to create diffuse texture. No path set.\n"));

	hasDiffuseTexture = true;
	//we need to parse the path to get the correct folder
	for (size_t i = modelPath.length(); i > 0; i--)
	{
		if (modelPath[i] != '/')
			modelPath.erase(i);
		else
			break;
	}
	//now we need to convert it to wstring
	modelPath += difTexPath;
	std::wstring path = std::wstring(modelPath.begin(), modelPath.end());

	if (FAILED(DirectX::CreateWICTextureFromFile(pDev, path.c_str(), &m_DiffuseTexture, &m_DiffuseTextureView)))
	{
		throw(std::runtime_error("ERROR: Unable to create diffuse texture.\n"));
		hasDiffuseTexture = false;
	}
}

void Mesh::createNormalSRV(ID3D11Device * pDev, std::string modelPath)
{
	if (normTexPath.length() < 4)
		throw(std::runtime_error("ERROR: Unable to create normal texture. No path set.\n"));

	hasNormalTexture = true;
	//we need to parse the path to get the correct folder
	for (size_t i = modelPath.length(); i > 0; i--)
	{
		if (modelPath[i] != '/')
			modelPath.erase(i);
		else
			break;
	}
	//now we need to convert it to wstring
	modelPath += normTexPath;
	std::wstring path = std::wstring(modelPath.begin(), modelPath.end());

	if (FAILED(DirectX::CreateWICTextureFromFile(pDev, path.c_str(), &m_NormalTexture, &m_NormalTextureView)))
	{
		throw(std::runtime_error("ERROR: Unable to create normal texture.\n"));
		hasNormalTexture = false;
	}
}

void Mesh::createSpecularSRV(ID3D11Device * pDev, std::string modelPath)
{
	if (specTexPath.length() < 4)
		throw(std::runtime_error("ERROR: Unable to create specular texture. No path set.\n"));

	hasSpecularTexture = true;
	//we need to parse the path to get the correct folder
	for (size_t i = modelPath.length(); i > 0; i--)
	{
		if (modelPath[i] != '/')
			modelPath.erase(i);
		else
			break;
	}
	//now we need to convert it to wstring
	modelPath += specTexPath;
	std::wstring path = std::wstring(modelPath.begin(), modelPath.end());

	if (FAILED(DirectX::CreateWICTextureFromFile(pDev, path.c_str(), &m_SpecularTexture, &m_SpecularTextureView)))
	{
		throw(std::runtime_error("ERROR: Unable to create specular texture.\n"));
		hasSpecularTexture = false;
	}
}

void Mesh::createBoundingShapeFromPoints(int type, float scaling, const XMFLOAT3 * arrPtr, size_t nrOf, size_t stride)
{
	Vector3 scaledExtents;
	float scaledRadius;
	switch (type)
	{
	case BOUNDINGTYPE::OBB:
		DirectX::BoundingOrientedBox::CreateFromPoints(m_OBB, nrOf, arrPtr, stride);
		scaledExtents = m_OBB.Extents;
		m_OBB.Extents = (scaledExtents * scaling);
		hasOBB = true;
		hasNoBoundingShape = false;
		break;
	case BOUNDINGTYPE::SPHERE:
		DirectX::BoundingSphere::CreateFromPoints(m_Sphere, nrOf, arrPtr, stride);
		scaledRadius = m_Sphere.Radius * scaling;
		m_Sphere.Radius = scaledRadius;
		hasSphere = true;
		hasNoBoundingShape = false;
		break;
	case BOUNDINGTYPE::AABB:
		DirectX::BoundingBox::CreateFromPoints(m_AABB, nrOf, arrPtr, stride);
		scaledExtents = m_AABB.Extents;
		m_AABB.Extents = (scaledExtents * scaling);
		hasAABB = true;
		hasNoBoundingShape = false;
		break;
	case BOUNDINGTYPE::TERRAIN:
		isTerrain = true;
		hasNoBoundingShape = true;
		break;
	case BOUNDINGTYPE::NONE:
		hasNoBoundingShape = true;
		break;
	default:
		hasNoBoundingShape = true;
		break;
	}
}

void Mesh::createBoungingShapeFromType(int type, float scaling)
{
	std::vector<XMFLOAT3> points = this->getAllPositions();
	size_t stride = sizeof(XMFLOAT3);
	Vector3 scaledExtents;
	float scaledRadius;

	if (hasNoBoundingShape)
	{
		switch (type)
		{
		case BOUNDINGTYPE::OBB:
			DirectX::BoundingOrientedBox::CreateFromPoints(m_OBB, points.size(), points.data(), stride);
			scaledExtents = m_OBB.Extents;
			m_OBB.Extents = (scaledExtents * scaling);
			hasOBB = true;
			break;
		case BOUNDINGTYPE::SPHERE:
			DirectX::BoundingSphere::CreateFromPoints(m_Sphere, points.size(), points.data(), stride);
			scaledRadius = m_Sphere.Radius * scaling;
			m_Sphere.Radius = scaledRadius;
			hasSphere = true;
			break;
		case BOUNDINGTYPE::AABB:
			DirectX::BoundingBox::CreateFromPoints(m_AABB, points.size(), points.data(), stride);
			scaledExtents = m_AABB.Extents;
			m_AABB.Extents = (scaledExtents * scaling);
			hasAABB = true;
			break;
		default:
			hasNoBoundingShape = true;
			break;
		}
	}
	points.clear();
}

void Mesh::Update(Matrix transformation)
{
	if (hasOBB)
		m_OBB.Transform(m_OBB, transformation);
}

std::vector<Vector3> Mesh::getTerrainPoints()
{
	//since we know this is terrain we also know which vector contains the mesh data
	std::vector<Vector3> m_points;
	for (size_t i = 0; i < vertices_PNC.size(); i++)
	{
		m_points.push_back(Vector3(vertices_PNC[i].position));
	}
	return m_points;
}

std::vector<XMFLOAT3> Mesh::getAllPositions()
{
	std::vector<XMFLOAT3> m_points;
	if (hasPos)
	{
		for (size_t i = 0; i < vertices_P.size(); i++)
		{
			m_points.push_back(vertices_P[i].position);
		}
		return m_points;
	}
	else if (hasPosCol)
	{
		for (size_t i = 0; i < vertices_PC.size(); i++)
		{
			m_points.push_back(vertices_PC[i].position);
		}
		return m_points;
	}
	else if (hasPosTex)
	{
		for (size_t i = 0; i < vertices_PT.size(); i++)
		{
			m_points.push_back(vertices_PT[i].position);
		}
		return m_points;
	}
	else if (hasPosNor)
	{
		for (size_t i = 0; i < vertices_PN.size(); i++)
		{
			m_points.push_back(vertices_PN[i].position);
		}
		return m_points;
	}
	else if (hasPosNorCol)
	{
		for (size_t i = 0; i < vertices_PNC.size(); i++)
		{
			m_points.push_back(vertices_PNC[i].position);
		}
		return m_points;
	}
	else if (hasPosNorTex)
	{
		for (size_t i = 0; i < vertices_PNT.size(); i++)
		{
			m_points.push_back(vertices_PNT[i].position);
		}
		return m_points;
	}
	else if (hasPosColTex)
	{
		for (size_t i = 0; i < vertices_PCT.size(); i++)
		{
			m_points.push_back(vertices_PCT[i].position);
		}
		return m_points;
	}
	else if (hasPosNorColTex)
	{
		for (size_t i = 0; i < vertices_PNCT.size(); i++)
		{
			m_points.push_back(vertices_PNCT[i].position);
		}
		return m_points;
	}
	else if (hasPosNorTanColTex)
	{
		for (size_t i = 0; i < vertices_PNTCT.size(); i++)
		{
			m_points.push_back(vertices_PNTCT[i].position);
		}
		return m_points;
	}

	return m_points;
}