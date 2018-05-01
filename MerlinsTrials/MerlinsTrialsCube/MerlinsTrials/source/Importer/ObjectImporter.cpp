#include "stdafx.h"
#include "ObjectImporter.h"



void ObjectImporter::debugString(const LPCWSTR &in_string, const aiReturn &in_param)
{
	if (AI_SUCCESS != in_param)
	{
		OutputDebugString(in_string);
	}
}

void  ObjectImporter::_fillWithPos(std::vector<Mesh*> &ppMesh, size_t index, aiMesh* t_mesh, ID3D11Device * pDev)
{
	ppMesh[index]->vertices_P.resize(t_mesh->mNumVertices); //allocate memory
	ppMesh[index]->setVertexCount(t_mesh->mNumVertices);
	ppMesh[index]->hasPos = true;

	for (UINT32 m = 0; m < t_mesh->mNumVertices; m++)
	{
		DirectX::VertexPosition t_p;
		t_p.position = DirectX::XMFLOAT3(t_mesh->mVertices[m].x, t_mesh->mVertices[m].y, t_mesh->mVertices[m].z);
		//add the vertex to the correct vector
		ppMesh[index]->vertices_P[m] = t_p;
	}

	//all vectors are filled with data, time to create the buffers
	try {
		ppMesh[index]->createBuffers(pDev);
	}
	catch (std::exception &e)
	{
		exit(-1);
	}
}

void ObjectImporter::_fillWithPosNorm(std::vector<Mesh*>& ppMesh, size_t index, aiMesh * t_mesh, ID3D11Device * pDev)
{
	ppMesh[index]->vertices_PN.resize(t_mesh->mNumVertices); //allocate memory
	ppMesh[index]->setVertexCount(t_mesh->mNumVertices);
	ppMesh[index]->hasPosNor = true;

	for (UINT32 m = 0; m < t_mesh->mNumVertices; m++)
	{
		DirectX::VertexPositionNormal t_pn;
		t_pn.position = DirectX::XMFLOAT3(t_mesh->mVertices[m].x, t_mesh->mVertices[m].y, t_mesh->mVertices[m].z);
		t_pn.normal = DirectX::XMFLOAT3(t_mesh->mNormals[m].x, t_mesh->mNormals[m].y, t_mesh->mNormals[m].z);
		//add the vertex to the correct vector
		ppMesh[index]->vertices_PN[m] = t_pn;
	}

	//all vectors are filled with data, time to create the buffers
	try {
		ppMesh[index]->createBuffers(pDev);
	}
	catch (std::exception &e)
	{
		exit(-1);
	}
}

void ObjectImporter::_fillWithPosNormTex(std::vector<Mesh*> &ppMesh, size_t index, aiMesh* t_mesh, ID3D11Device * pDev)
{
	ppMesh[index]->vertices_PNT.resize(t_mesh->mNumVertices); //allocate memory
	ppMesh[index]->setVertexCount(t_mesh->mNumVertices);
	ppMesh[index]->hasPosNorTex = true;

	for (UINT32 m = 0; m < t_mesh->mNumVertices; m++)
	{
		DirectX::VertexPositionNormalTexture t_pnt;
		t_pnt.position = DirectX::XMFLOAT3(t_mesh->mVertices[m].x, t_mesh->mVertices[m].y, t_mesh->mVertices[m].z);
		t_pnt.normal = DirectX::XMFLOAT3(t_mesh->mNormals[m].x, t_mesh->mNormals[m].y, t_mesh->mNormals[m].z);
		t_pnt.textureCoordinate = DirectX::XMFLOAT2(t_mesh->mTextureCoords[0][m].x, t_mesh->mTextureCoords[0][m].y);

		//add the vertex to the correct vector
		ppMesh[index]->vertices_PNT[m] = t_pnt;
	}
	try {
		ppMesh[index]->createBuffers(pDev);
	}
	catch (std::exception &e)
	{
		exit(-1);
	}
}

ObjectImporter::ObjectImporter()
{
}

ObjectImporter::~ObjectImporter()
{
}

bool ObjectImporter::importOBJModel(const std::string & path, std::vector<Mesh*> &ppMesh, ID3D11Device * pDev, ID3D11DeviceContext * pDevCon)
{
	const ::aiScene* t_scene = this->importer.ReadFile(
		path.c_str(), 
		aiProcess_Triangulate 
		| aiProcess_JoinIdenticalVertices 
		| aiProcess_MakeLeftHanded);

	if (!t_scene)
	{
		std::string exp = importer.GetErrorString();
		OutputDebugString(std::wstring(exp.begin(), exp.end()).c_str());
		return false;
	}

	if (!t_scene->HasMeshes())
		throw std::runtime_error("ERROR: Loaded object contained no meshes.\n");

	ppMesh.resize(t_scene->mNumMeshes);

	for (UINT32 i = 0; i < t_scene->mNumMeshes; i++)
	{
		ppMesh[i] = new Mesh();
		aiMesh* t_mesh = t_scene->mMeshes[i];
		unsigned int mIndx = t_mesh->mMaterialIndex;
		aiMaterial* mtl = t_scene->mMaterials[mIndx];

		ppMesh[i]->setName(t_mesh->mName.C_Str());

		//handle the faces and fill the index buffer
		if (t_mesh->HasFaces())
		{
			::aiFace *t_faces = t_mesh->mFaces;
			int numOfFaces = t_mesh->mNumFaces;
			ppMesh[i]->indices.resize(t_mesh->mNumFaces * 3); //allocate memory

			for (UINT32 j = 0; j < t_mesh->mNumFaces; j++)
			{
				if (t_faces[j].mNumIndices != 3)
				{
					importer.FreeScene();
					throw std::runtime_error("ERROR: Mesh not triangulated.");
				}
				
				for (UINT32 k = 0; k < 3; k++)
				{
					ppMesh[i]->indices[j * 3 + k] = t_faces[j].mIndices[k];
				}
			}
		}

		ppMesh[i]->setFaceCount(t_mesh->mNumFaces);
	
		//if pos, normal and uvs are present, load int that vertextype
		if (t_mesh->HasPositions() && t_mesh->HasNormals() && t_mesh->HasTextureCoords(0))
		{
			this->_fillWithPosNormTex(ppMesh, i, t_mesh, pDev);
		} //if pos and normals are present but no texture
		else if (t_mesh->HasPositions() && t_mesh->HasNormals() && !t_mesh->HasTextureCoords(0))
		{
			this->_fillWithPosNorm(ppMesh, i, t_mesh, pDev);
		} //if only positions are present
		else if (t_mesh->HasPositions() && !t_mesh->HasNormals() && !t_mesh->HasTextureCoords(0))
		{
			this->_fillWithPos(ppMesh, i, t_mesh, pDev);
		}
		else
			throw std::runtime_error("ERROR: No matched vertex formats\n");

		//add the material properties to the mesh
		aiReturn rValue;
		aiString aiPath;
		DirectX::SimpleMath::Vector3 vec3;
		aiColor3D cColor(0.0f, 0.0f, 0.0f);
		float nsSpecularExponent = 0.0f;
		float dOpacity = 0.0f;

		rValue = mtl->Get(AI_MATKEY_SHININESS, nsSpecularExponent);
		ppMesh[i]->setSpecExponent(nsSpecularExponent);

		mtl->Get(AI_MATKEY_OPACITY, dOpacity);
		ppMesh[i]->setOpacity(dOpacity);

		mtl->Get(AI_MATKEY_COLOR_DIFFUSE, cColor);
		vec3 = DirectX::SimpleMath::Vector3(cColor.r, cColor.g, cColor.b);
		ppMesh[i]->setDiffuse(vec3);

		mtl->Get(AI_MATKEY_COLOR_AMBIENT, cColor);
		vec3 = DirectX::SimpleMath::Vector3(cColor.r, cColor.g, cColor.b);
		ppMesh[i]->setAmbient(vec3);

		mtl->Get(AI_MATKEY_COLOR_SPECULAR, cColor);
		vec3 = DirectX::SimpleMath::Vector3(cColor.r, cColor.g, cColor.b);
		ppMesh[i]->setSpec(vec3);

		mtl->Get(AI_MATKEY_COLOR_EMISSIVE, cColor);
		vec3 = DirectX::SimpleMath::Vector3(cColor.r, cColor.g, cColor.b);
		ppMesh[i]->setEmissive(vec3);

		::aiGetMaterialTexture(mtl, aiTextureType_DIFFUSE, 0, &aiPath);
		ppMesh[i]->setDifTexPath(aiPath.C_Str());
		aiPath.Clear();

		::aiGetMaterialTexture(mtl, aiTextureType_NORMALS, 0, &aiPath);
		ppMesh[i]->setNormTexPath(aiPath.C_Str());
		aiPath.Clear();

		::aiGetMaterialTexture(mtl, aiTextureType_SPECULAR, 0, &aiPath);
		ppMesh[i]->setSpecTexPath(aiPath.C_Str());
		aiPath.Clear();
		
		try {
			ppMesh[i]->createDiffuseSRV(pDev, path);
			ppMesh[i]->createNormalSRV(pDev, path);
			ppMesh[i]->createSpecularSRV(pDev, path);
		}
		catch (std::exception &e)
		{
			std::string exc = e.what();
			OutputDebugString(std::wstring(exc.begin(), exc.end()).c_str());
		}
	}

}
