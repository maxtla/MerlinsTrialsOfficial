#ifndef WALLMANAGER_H
#define WALLMANAGER_H
#include<vector>
#include"WallModel.h"
#include<d3d11.h>

class WallManager
{
private:
	std::vector<WallModel>* models;
	std::vector<WallModel>* otherModels;

	ID3D11Device * device;
	ID3D11DeviceContext * deviceContext;

public:
	WallManager();
	~WallManager();

	void Draw();
	void initialize(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext);
	void setModelPtr(std::vector<WallModel>* in_models, std::vector<WallModel>* in_otherModels);
	
	
};

#endif