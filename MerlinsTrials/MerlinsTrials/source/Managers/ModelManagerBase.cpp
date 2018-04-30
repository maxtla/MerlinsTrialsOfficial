#include "stdafx.h"
#include "ModelManagerBase.h"

ModelManagerBase::ModelManagerBase()
{
}

ModelManagerBase::ModelManagerBase(Camera * in_camera, ID3D11Device * in_device, ID3D11DeviceContext * in_context)
{
	this->camera = in_camera;
	this->device = in_device;
	this->context = in_context;
}

ModelManagerBase::~ModelManagerBase()
{
}
