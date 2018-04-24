#ifndef WATERMANAGER_H
#define WATERMANAGER_H
#include"WaterModel.h"

class WaterManager
{
private:


public:
	WaterManager();
	~WaterManager();

	void initialize(ID3D11Device * in_device, ID3D11DeviceContext * in_deviceContext);
	void setModelPtr(std::vector<WaterModel>* in_models);
};
#endif // !WATERMANAGER_H
