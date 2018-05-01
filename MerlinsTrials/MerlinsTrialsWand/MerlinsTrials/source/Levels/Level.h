#ifndef LEVEL_H
#define LEVEL_H
#include "..\Importer\ObjectImporter.h"
#include "..\Helpers\AssetsPaths.h"
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
	bool Update();
	void Draw(Matrix view, Matrix projection);

private:
	std::vector<Mesh*> m_StaticObjects;
	BasicShader * m_BasicColorShader;
	std::unique_ptr<PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
};

#endif // !LEVEL_H
