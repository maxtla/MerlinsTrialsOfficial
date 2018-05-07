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
	void DrawOBBS(PrimitiveBatch<DirectX::VertexPositionColor> *batch, Vector4 color);
};


#endif