#include"stdafx.h"
#include"Inventory.h"

Inventory::Inventory() {

	//Init d3d11 stuff
	this->dev = nullptr;
	this->devC = nullptr;

	//Init meshes
	this->cubes = new CubeModel*[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++) {

		this->cubes[i] = nullptr;

	}

	this->nrOfCubes = 0;
	this->selected = 0;

}

Inventory::~Inventory() {

	//Delete cubes arrau
	delete[] this->cubes;
	
	//Release textures
	this->barTexture.Reset();
	this->selectedTexture.Reset();
	this->redCubeTexture.Reset();
	this->blueCubeTexture.Reset();
	this->yellowCubeTexture.Reset();
	this->greenCubeTexture.Reset();

	//Release sprite batch
	this->spriteBatch.release();

}

////////////////////////////////////MISC//////////////////////////////////////
void Inventory::loadTexture(void) {

	//Load inventory bar texture
	HRESULT hr = NULL;
	hr = CreateWICTextureFromFile(this->dev, 
		L".//Assets//InventoryAssets//Inventory.png", nullptr,
		this->barTexture.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {

		exit(-1);

	}

	//Load Selected texture
	hr = CreateWICTextureFromFile(this->dev,
		L".//Assets//InventoryAssets//Selected.png", nullptr,
		this->selectedTexture.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {

		exit(-1);

	}

	//Load Cube textures
	hr = CreateWICTextureFromFile(this->dev,
		L".//Assets//InventoryAssets//BlueCube.png", nullptr,
		this->blueCubeTexture.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {

		exit(-1);

	}

	hr = CreateWICTextureFromFile(this->dev,
		L".//Assets//InventoryAssets//RedCube.png", nullptr,
		this->redCubeTexture.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {

		exit(-1);

	}

	hr = CreateWICTextureFromFile(this->dev,
		L".//Assets//InventoryAssets//GreenCube.png", nullptr,
		this->greenCubeTexture.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {

		exit(-1);

	}

	hr = CreateWICTextureFromFile(this->dev,
		L".//Assets//InventoryAssets//YellowCube.png", nullptr,
		this->yellowCubeTexture.ReleaseAndGetAddressOf());

	if (FAILED(hr)) {

		exit(-1);

	}

}

void Inventory::init(std::vector<Mesh*> barMesh, BasicShader* basicS, 
	ID3D11Device* device, ID3D11DeviceContext* deviceC) {

	//D3D11 Stuff
	this->dev = device;
	this->devC = deviceC;

	//Init sprite batch
	this->spriteBatch = std::make_unique<SpriteBatch>(this->devC);

	//Load Textures
	this->loadTexture();

}

void Inventory::draw(DirectX::XMMATRIX view, DirectX::XMMATRIX proj) {

	//Draw UI
	this->spriteBatch->Begin();

	this->spriteBatch->Draw(this->barTexture.Get(), Vector2(10.0f, 950.0f));
	this->spriteBatch->Draw(this->selectedTexture.Get(), 
		Vector2(14.0f + (float(INV_OFFSET) * this->selected), 954.0f));

	for (int i = 0; i < MAXSIZE; i++) {

		if (this->cubes[i] != nullptr) {

			switch (this->cubes[i]->getID()) {

			case 0:
				this->spriteBatch->Draw(this->redCubeTexture.Get(),
					Vector2(19 + (float(INV_OFFSET) * float(i)), 974.0f));
				break;
			case 1:
				this->spriteBatch->Draw(this->greenCubeTexture.Get(),
					Vector2(19 + (float(INV_OFFSET) * float(i)), 974.0f));
				break;
			case 2:
				this->spriteBatch->Draw(this->blueCubeTexture.Get(),
					Vector2(19 + (float(INV_OFFSET) * float(i)), 974.0f));
				break;
			case 3:
				this->spriteBatch->Draw(this->yellowCubeTexture.Get(),
					Vector2(19 + (float(INV_OFFSET) * float(i)), 974.0f));
				break;
			default:
				break;
			}

		}

	}

	this->spriteBatch->End();

}

void Inventory::update(DirectX::XMMATRIX view) {



}

bool Inventory::addCube(CubeModel* cube) {

	//Add cube
	bool added = false;

	//Check if inventory is full
	if (this->nrOfCubes < MAXSIZE) {

		//Add to seleced slot if empty
		if (this->cubes[this->selected] == nullptr) {

			this->cubes[this->selected] = cube;

		}
		else {

			//Add to first best empty slot
			for (int i = 0; i < MAXSIZE; i++) {

				if (this->cubes[i] == nullptr) {

					this->cubes[i] = cube;
					break;
				}

			}

		}

		//Increase size
		this->nrOfCubes++;
		added = true;

	}

	return added;

}

CubeModel* Inventory::removeCube(int id) {

	//Remove cube
	CubeModel* tempCube = nullptr;

	//Check if selected is empty
	if (this->cubes[this->selected] != nullptr) {

		//Check if the selected cube is correct
		if (this->cubes[this->selected]->getID() == id) {
			
			//Assigne cube to temp and rempve from inventory
			tempCube = this->cubes[this->selected];
			this->cubes[this->selected] = nullptr;
			this->nrOfCubes--;

		}

	}

	return tempCube;

}

CubeModel* Inventory::reset(int id)
{
	//Remove cube
	CubeModel* tempCube = nullptr;
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (this->cubes[i] != nullptr && this->cubes[i]->getID() == id)
		{
			//Assigne cube to temp and rempve from inventory
			tempCube = this->cubes[i];
			this->cubes[i] = nullptr;
			this->nrOfCubes--;
			break;
		}
		
	}


	return tempCube;
}

////////////////////////////////////GET/////////////////////////////////////////
int Inventory::getSelected(void) const{

	return this->selected;

}

////////////////////////////////////SET///////////////////////////////////////////
void Inventory::setSelected(int index) {

	this->selected = index;

}

