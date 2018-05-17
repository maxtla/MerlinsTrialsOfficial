#pragma once
#ifndef ROCK_MODEL_H
#define ROCK_MODEL_H
#include "ModelBase.h"

class RockModel : public ModelBase
{
private:

public:
	RockModel(Matrix world, bool isVisible, bool isSolid);
	~RockModel();
	void Draw(BasicShader * pBasicShader);
	void DrawOBBS(BasicShader * pBasicShader, PrimitiveBatch<DirectX::VertexPositionColor> *batch, Matrix view, Matrix proj, Vector4 color);
};


#endif