#ifndef INVENTORY_H
#define INVENTORY_H

#include<d3d11.h>
#include "SimpleMath.h"
#include<DirectXMath.h>
#include "..\Importer\Mesh.h"
#include"..\Objects\CubeModel.h"
#include"SpriteBatch.h"

static const int MAXSIZE = 4;
static const int INV_OFFSET = 100;

class Inventory {

private:

	//D3D11 Stuff
	ID3D11DeviceContext * devC;
	ID3D11Device * dev;

	//UI Stuff
	std::unique_ptr<SpriteBatch> spriteBatch;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> barTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> selectedTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> redCubeTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> blueCubeTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> greenCubeTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> yellowCubeTexture;

	//Meshes
	CubeModel** cubes;

	//Misc
	int nrOfCubes;
	int selected;

	//Private functions
	void loadTexture(void);

public:

	Inventory();
	~Inventory();

	//Misc
	void init(std::vector<Mesh*> meshes, BasicShader* basicS, ID3D11Device* device, ID3D11DeviceContext* deviceC);
	void draw(DirectX::XMMATRIX view, DirectX::XMMATRIX projection);
	void update(DirectX::XMMATRIX view);
	bool addCube(CubeModel* cube);
	CubeModel* removeCube(int id);
	CubeModel* reset(int id);
	
	
	//Get
	int getSelected(void) const;


	//Set
	void setSelected(int index);

};

#endif // !INVENTORY_H
