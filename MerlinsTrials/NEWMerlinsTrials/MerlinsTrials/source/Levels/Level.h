#ifndef LEVEL_H
#define LEVEL_H
#include "..\Player\Player.h"
#include "..\Shaders\BasicShader.h"
#include <PrimitiveBatch.h>
#include<string>

using namespace DirectX::SimpleMath;

class Level
{

public:

	Level();
	~Level();

	bool initialize(std::vector<Mesh*> mesh, BasicShader * pBasicColorShader);
	bool Update(Player * player);
	void Draw(Matrix view, Matrix projection);

	BasicShader * m_BasicColorShader;
	std::unique_ptr<PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	std::vector<Mesh*> getLevelMeshes() const { return m_StaticObjects; }
private:
	std::vector<Mesh*> m_StaticObjects;
	//---used for terrain walking---
	std::vector<std::vector<Vector3>> terrainPointVectors;
	std::vector<std::vector<uint16_t>> terrainPointIndices;
	//------------------------------
};

#endif // !LEVEL_H
