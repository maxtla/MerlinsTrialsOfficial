#include "stdafx.h"
#include "CubeManager.h"

CubeManager::CubeManager()
{
}

CubeManager::~CubeManager()
{

	delete this->m_BasicShader;
	delete this->m_NormalMapShader;	
	delete this->pickupSound;
	delete this->putDownSound;

	this->m_BasicShader = nullptr;
	this->m_NormalMapShader = nullptr;

	this->m_ForestCubes.clear();
	this->m_LabyrinthCubes.clear();
	this->m_ForestPedestals.clear();
	this->m_LabyrinthPedestals.clear();	
}

bool CubeManager::initialize(ID3D11DeviceContext * pDevCon, ID3D11Device * pDev, Player* in_player, LevelState* in_state)
{
	this->pPlayer = in_player;
	this->context = pDevCon;
	this->device = pDev;
	this->state = in_state;

	this->m_BasicShader = new BasicShader();
	this->m_NormalMapShader = new NormalMapShader();

	this->m_BasicShader->init(pDev, pDevCon);
	this->m_BasicShader->createShader(SHADERTYPE::VertexPosNormCol);
	this->m_NormalMapShader->init(pDev, pDevCon);
	this->m_NormalMapShader->createShader(NORMALMAP_SHADER_TYPE::WITH_COLOR);

	//Init sound
	this->putDownSound = new SoundEngine();
	this->putDownSound->loadSound(PUT_DOWN_SOUND_PATH);
	this->putDownSound->setSoundVolume(30);

	this->pickupSound = new SoundEngine();
	this->pickupSound->loadSound(PICKUP_SOUND_PATH);
	this->pickupSound->setSoundVolume(30);

	this->eraseId = -1;
	this->cubeIsAboutToBeErased = false;
	this->eraseDelay.startTimer();

	return true;
}

bool CubeManager::checkPickUp()
{
	if (this->pPlayer->synchGrabKey() && this->eraseDelay.frameDiff() > 400)
	{
		this->checkCollision();
	}
	return false;
}

void CubeManager::resetLabyCubesPos()
{
	for (auto var : this->m_LabyrinthCubes)
	{
		switch (var->getID())
		{
		case 0:
		{
			var->setWorld(this->redCubeLaby);
		}
		break;
		case 1:
		{
			var->setWorld(this->greenCubeLaby);
		}
		break;
		case 2:
		{
			var->setWorld(this->blueCubeLaby);
		}
		break;
		case 3:
		{
			var->setWorld(this->yellowCubLaby);
		}
		break;
		}
	}
}

void CubeManager::eraseCube()
{
	switch (this->state->getLevel())
	{
	case CURRENT_LEVEL::ONE:
	{
		switch (this->state->getPhase())
		{
		case PUZZLE_PHASE::FIRST:
		{
			this->m_ForestCubes.erase(this->m_ForestCubes.begin() + eraseId);
			break;
		}
		case PUZZLE_PHASE::SECOND:
		{
			this->m_LabyrinthCubes.erase(this->m_LabyrinthCubes.begin() + eraseId);
			break;
		}
		}
	}
	case CURRENT_LEVEL::TWO:
	{


	}
	break;
	case CURRENT_LEVEL::THREE:
	{



	}
	break;
	}

	this->cubeIsAboutToBeErased = false;
	this->eraseId = -1;
}

void CubeManager::initializeLevelOne()
{
	for (int i = 0; i < 4; i++)
	{
		this->m_ForestCubes.push_back(new CubeModel(XMMatrixIdentity(), true, true, i));
		this->m_LabyrinthCubes.push_back(new CubeModel(XMMatrixIdentity(), true, true, i));
		this->m_ForestPedestals.push_back(new PedestalModel(XMMatrixIdentity() * XMMatrixTranslation(0.f, 0.f, 2.f), true, true, i));
		this->m_LabyrinthPedestals.push_back(new PedestalModel(XMMatrixIdentity() * XMMatrixTranslation(0.f, 0.f, -2.f), true, true, i));
		
		this->m_ForestCubes[i]->setBasicShader(this->m_BasicShader);
		this->m_LabyrinthCubes[i]->setBasicShader(this->m_BasicShader);
		this->m_ForestPedestals[i]->setBasicShader(this->m_BasicShader);
		this->m_LabyrinthPedestals[i]->setBasicShader(this->m_BasicShader);
		
		switch (i)
		{
		case 0:
		{
			//red cubes
			this->m_ForestCubes[i]->loadModel(CUBES_PATH0, this->device, this->context);
			this->m_ForestCubes[i]->setWorld(this->redCubeForest);
			this->m_LabyrinthCubes[i]->loadModel(CUBES_PATH0, this->device, this->context);
			this->m_LabyrinthCubes[i]->setWorld(this->redCubeLaby);

			//röd
			this->m_ForestPedestals[i]->loadModel(PEDI_PATH0, this->device, this->context);
			this->m_ForestPedestals[i]->setWorld(XMMatrixRotationX(XM_PI / 2) * XMMatrixTranslation(-8.8f, -.8f, -2.5f));
			this->m_LabyrinthPedestals[i]->loadModel(PEDI_PATH0, this->device, this->context);
			this->m_LabyrinthPedestals[i]->setWorld(XMMatrixRotationX(XM_PI / 2) * XMMatrixTranslation(-18.7035f, -.8f, 2.6798f));
		}
		break;
		case 1:
		{
			this->m_ForestCubes[i]->loadModel(CUBES_PATH1, this->device, this->context);
			this->m_ForestCubes[i]->setWorld(this->greenCubeForest);
			this->m_LabyrinthCubes[i]->loadModel(CUBES_PATH1, this->device, this->context);
			this->m_LabyrinthCubes[i]->setWorld(this->greenCubeLaby);

			//grön
			this->m_ForestPedestals[i]->loadModel(PEDI_PATH1, this->device, this->context);
			this->m_ForestPedestals[i]->setWorld(XMMatrixRotationX(XM_PI / 2) * XMMatrixTranslation(-8.8f, -.8f, -1.5f));
			this->m_LabyrinthPedestals[i]->loadModel(PEDI_PATH1, this->device, this->context);
			this->m_LabyrinthPedestals[i]->setWorld(XMMatrixRotationX(XM_PI / 2) * XMMatrixTranslation(-17.7277f, -.8f, -2.6197f));
		}
		break;
		case 2:
		{
			//blå kub
			this->m_ForestCubes[i]->loadModel(CUBES_PATH2, this->device, this->context);
			this->m_ForestCubes[i]->setWorld(this->blueCubeForest);
			this->m_LabyrinthCubes[i]->loadModel(CUBES_PATH2, this->device, this->context);
			this->m_LabyrinthCubes[i]->setWorld(this->blueCubeLaby);

			//blå pedistal
			this->m_ForestPedestals[i]->loadModel(PEDI_PATH2, this->device, this->context);
			this->m_ForestPedestals[i]->setWorld(XMMatrixRotationX(XM_PI / 2) * XMMatrixTranslation(-8.8f, -.8f, 2.5f));
			this->m_LabyrinthPedestals[i]->loadModel(PEDI_PATH2, this->device, this->context);
			this->m_LabyrinthPedestals[i]->setWorld(XMMatrixRotationX(XM_PI / 2) * XMMatrixTranslation(-12.8989f, -.8f, 2.99004f));
		}
		break;
		case 3:
		{
			this->m_ForestCubes[i]->loadModel(CUBES_PATH3, this->device, this->context);
			this->m_ForestCubes[i]->setWorld(this->yellowCubForest);
			this->m_LabyrinthCubes[i]->loadModel(CUBES_PATH3, this->device, this->context);
			this->m_LabyrinthCubes[i]->setWorld(this->yellowCubLaby);
			//gul
			this->m_ForestPedestals[i]->loadModel(PEDI_PATH3, this->device, this->context);
			this->m_ForestPedestals[i]->setWorld(XMMatrixRotationX(XM_PI / 2) * XMMatrixTranslation(-8.8f, -.8f, 1.5f));
			this->m_LabyrinthPedestals[i]->loadModel(PEDI_PATH3, this->device, this->context);
			this->m_LabyrinthPedestals[i]->setWorld(XMMatrixRotationX(XM_PI / 2) * XMMatrixTranslation(-11.3949f, -.8f, -1.4f));
		}
		break;
		}
	}

}

void CubeManager::initializeLevelTwo()
{
}

void CubeManager::swapDimension()
{

	PUZZLE_PHASE cPhase = this->state->getPhase();
	Dimension cDim = this->state->getDimension();
	CURRENT_LEVEL cLvl = this->state->getLevel();

	switch (cLvl)
	{
	case CURRENT_LEVEL::ONE:
	{
		if (cPhase == PUZZLE_PHASE::FIRST)
		{
			//PHASE ONE - swap on cubes
			switch (cDim)
			{
			case Dimension::NORMAL:

				for (auto var : this->m_ForestCubes)
				{
					if (!var->getOnPedistal())
					{
						int id = var->getID();
						switch (id)
						{
						case 0:
							var->setVisisble(false);
							var->setSolid(false);
							break;
						case 1:
							var->setVisisble(false);
							var->setSolid(false);
							break;
						case 2:
							var->setVisisble(true);
							var->setSolid(true);
							break;
						case 3:
							var->setVisisble(true);
							var->setSolid(true);
							break;

						}
					}
				}

				break;
			case Dimension::OTHER:

				for (auto var : this->m_ForestCubes)
				{
					if (!var->getOnPedistal())
					{
						int id = var->getID();
						switch (id)
						{
						case 0:
							var->setVisisble(true);
							var->setSolid(true);
							break;
						case 1:
							var->setVisisble(true);
							var->setSolid(true);
							break;
						case 2:
							var->setVisisble(false);
							var->setSolid(false);
							break;
						case 3:
							var->setVisisble(false);
							var->setSolid(false);
							break;

						}
					}
				}
				break;
			}
		}
		else
		{
			//PHASE TWO - swap on pedistals
			switch (cDim)
			{
			case Dimension::NORMAL:
				for (auto var : this->m_LabyrinthPedestals)
				{
					int id = var->getID();
					switch (id)
					{
					case 0:
						var->setVisisble(true);
						var->setSolid(true);
						break;
					case 1:
						var->setVisisble(true);
						var->setSolid(true);
						break;
					case 2:
						var->setVisisble(false);
						var->setSolid(false);
						break;
					case 3:
						var->setVisisble(false);
						var->setSolid(false);
						break;

					}
				}
				break;
			case Dimension::OTHER:
				for (auto var : this->m_LabyrinthPedestals)
				{
					int id = var->getID();
					switch (id)
					{
					case 0:
						var->setVisisble(false);
						var->setSolid(false);
						break;
					case 1:
						var->setVisisble(false);
						var->setSolid(false);
						break;
					case 2:
						var->setVisisble(true);
						var->setSolid(true);
						break;
					case 3:
						var->setVisisble(true);
						var->setSolid(true);
						break;

					}
				}
				break;
			}
		}
	
	}
		break;
		case CURRENT_LEVEL::TWO:
	{



	}
		break;
		case CURRENT_LEVEL::THREE:
	{



	}
		break;
	}

	

}

void CubeManager::SwapPhases()
{
	PUZZLE_PHASE cPhase = this->state->getPhase();
	CURRENT_LEVEL cLvl = this->state->getLevel();

	switch (cLvl)
	{
		case CURRENT_LEVEL::ONE:
		{
			switch (cPhase)
			{
			case PUZZLE_PHASE::FIRST:
				for (auto var : this->m_ForestPedestals)
				{
					var->setVisisble(true);
					var->setSolid(true);
				}
				for (auto var : this->m_ForestCubes)
				{
					var->setVisisble(true);
					var->setSolid(true);
				}
				for (auto var : this->m_LabyrinthPedestals)
				{
					var->setVisisble(false);
					var->setSolid(false);
				}
				for (auto var : this->m_LabyrinthCubes)
				{
					var->setVisisble(false);
					var->setSolid(false);
				}
				break;
			case PUZZLE_PHASE::SECOND:
				for (auto var : this->m_ForestPedestals)
				{
					var->setVisisble(false);
					var->setSolid(false);
				}
				for (auto var : this->m_ForestCubes)
				{
					var->setVisisble(false);
					var->setSolid(false);
				}
				for (auto var : this->m_LabyrinthPedestals)
				{
					var->setVisisble(true);
					var->setSolid(true);
				}
				for (auto var : this->m_LabyrinthCubes)
				{
					var->setVisisble(true);
					var->setSolid(true);
				}

				break;
			}
		}
			break;
		case CURRENT_LEVEL::TWO:
		{




		}
			break;
		case CURRENT_LEVEL::THREE:
		{





		}
			break;
	}

	
}

void CubeManager::update()
{
	if (this->pPlayer->synchRealmKey(this->state))
	{
		this->swapDimension();
	}
	this->checkPickUp();
	this->checkCubesOnPedistal();
	
	if (this->cubeIsAboutToBeErased == true && this->eraseDelay.frameDiff() >= 350)
	{
		this->eraseCube();		
	}
}

void CubeManager::Draw(DirectX::XMMATRIX in_Proj, DirectX::XMMATRIX in_View)
{

	this->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->m_BasicShader->setBlendState();
	this->m_BasicShader->setDepthStencilState();
	this->m_BasicShader->setRasterizerState(CULL_CLOCKWISE_STATE);
	this->m_BasicShader->setSamplerState();

	for (auto var : this->m_ForestCubes)
	{
		this->m_BasicShader->m_effect->SetMatrices(var->getWorld(), in_View, in_Proj);
		if (var->getVisisble())
		{
			var->Draw(this->context, in_View, in_Proj);
		}
	}
	for (auto var : this->m_LabyrinthCubes)
	{
		this->m_BasicShader->m_effect->SetMatrices(var->getWorld(), in_View, in_Proj);
		if (var->getVisisble())
		{
			var->Draw(this->context, in_View, in_Proj);
		}
	}
	for (auto var : this->m_LabyrinthPedestals)
	{
		//this->m_BasicShader->m_effect->SetMatrices(var->getWorld(), in_View, in_Proj);
		if (var->getVisisble())
		{
			var->Draw(this->context, in_View, in_Proj);
		}
	}
	for (auto var : this->m_ForestPedestals)
	{
		//this->m_BasicShader->m_effect->SetMatrices(var->getWorld(), in_View, in_Proj);
		if (var->getVisisble())
		{
			int x = var->getID();
			var->Draw(this->context, in_View, in_Proj);
		}
	}

}

void CubeManager::reset()
{
	switch (this->state->getLevel())
	{
		case CURRENT_LEVEL::ONE:
		{
			switch (this->state->getPhase())
			{
				case PUZZLE_PHASE::SECOND:
				{
					if (this->m_LabyrinthCubes.size() < 4)
					{
						for (int i = 0; i < NR_OF_CUBES; i++)
						{
							CubeModel*  model = this->pPlayer->getInventory()->reset(i);
							if (model != nullptr)
							{
								this->m_LabyrinthCubes.push_back(model);
							}
						}
						this->resetLabyCubesPos();

					}
					else
					{
						//reset positions
						this->resetLabyCubesPos();

					}
					
				}
					break;
			}
		}
			break;
		case CURRENT_LEVEL::THREE:
		{

			break;
		}
	
	
	}

}

void CubeManager::checkCubesOnPedistal()
{
	unsigned int counter = 0;
	switch (this->state->getPhase())
	{
	case PUZZLE_PHASE::FIRST:
		for (auto var : this->m_ForestCubes)
		{
			if (var->getOnPedistal())
			{				
				counter++;
			}
		}
		this->state->setFCubes(counter);

		break;
	case PUZZLE_PHASE::SECOND:
		for (auto var : this->m_LabyrinthCubes)
		{
			if (var->getOnPedistal())
			{
				counter++;
			}
		}
		this->state->setFCubes(counter);
		//GAME DONE/RIP
		break;
	}
}

int CubeManager::checkCollision()
{
	PUZZLE_PHASE cPhase = this->state->getPhase();
	CURRENT_LEVEL cLvl = this->state->getLevel();

	float distance = INFINITY; //some standard value
	XMVECTOR forwardVec = this->pPlayer->getCam()->getCamForward();
	XMVECTOR camPos = this->pPlayer->getCam()->getCamPos();
	int id = -1;
	CubeModel* model = nullptr;

	switch (cLvl)
	{
	case CURRENT_LEVEL::ONE:
	{

		switch (cPhase)
		{
		case PUZZLE_PHASE::FIRST:
			//check collisions with cubes for forest
			for (auto var : this->m_ForestCubes)
			{
				DirectX::BoundingBox box = var->getBoundingBox();
				box.Transform(box, var->getWorld());
				if (var->getSolid() && box.Intersects(camPos, forwardVec, distance))
				{
					//Intersects
					if (distance <= var->getGrabDistance())
					{
						//within range
						//add cube to inventory
						id = var->getID();
						break;

					}
				}
			}
			if (id == -1)
			{

				for (auto var : this->m_ForestPedestals)
				{
					DirectX::BoundingOrientedBox box = var->getBoundingBox();
					box.Transform(box, var->getWorld());
					box.Transform(box, XMMatrixTranslation(0.f, .2f, 0.f));

					if (var->getSolid() && box.Intersects(camPos, forwardVec, distance))
					{
						if (distance <= var->getGrabDistance())
						{
							id = var->getID();
							break;
						}
					}
				}
				if (id != -1)
				{
					model = this->pPlayer->getInventory()->removeCube(id);
					if (model != nullptr)
					{
						this->pPlayer->getWand()->resetPickupTimer();
						this->pPlayer->getWand()->setInPickupAnimation(true);

						XMMATRIX pWorld;
						for (auto var : this->m_ForestPedestals)
						{

							if (id == var->getID())
							{
								pWorld = var->getWorld();
								break;
							}
						}
						XMVECTOR vec;
						XMVECTOR dumb;
						XMMatrixDecompose(&dumb, &dumb, &vec, pWorld);

						XMMATRIX pos;
						pos = XMMatrixTranslationFromVector(vec);
						pos *= XMMatrixTranslation(0.f, 1.35f, 0.f);

						model->setWorld(pos);
						model->setOnPedistal(true);
						this->m_ForestCubes.push_back(model);						
						this->putDownSound->playSound();
					}
				}
			}
			else
			{

				for (int i = 0; i < this->m_ForestCubes.size(); i++)
				{
					if (this->m_ForestCubes.at(i)->getID() == id)
					{
						this->pickupSound->playSound();
						model = this->m_ForestCubes[i];						
						this->pPlayer->getInventory()->addCube(model);
						this->pPlayer->getWand()->resetPickupTimer();
						this->pPlayer->getWand()->setInPickupAnimation(true);						
						this->eraseId = i;
						this->cubeIsAboutToBeErased = true;
						this->eraseDelay.reset();

						break;
					}
				}

			}
			break;
		case PUZZLE_PHASE::SECOND:
			//check collisions with cubes for forest
			for (auto var : this->m_LabyrinthCubes)
			{
				DirectX::BoundingBox box = var->getBoundingBox();
				box.Transform(box, var->getWorld());

				if (var->getSolid() && box.Intersects(camPos, forwardVec, distance))
				{
					//Intersects
					if (distance <= var->getGrabDistance())
					{
						//within range
						//add cube to inventory
						id = var->getID();
						break;

					}
				}
			}
			if (id == -1)
			{

				for (auto var : this->m_LabyrinthPedestals)
				{
					DirectX::BoundingOrientedBox box = var->getBoundingBox();
					box.Transform(box, var->getWorld());
					box.Transform(box, XMMatrixTranslation(0.f, .2f, 0.f));

					if (var->getSolid() && box.Intersects(camPos, forwardVec, distance))
					{
						if (distance <= var->getGrabDistance())
						{
							id = var->getID();
							break;
						}
					}
				}
				if (id != -1)
				{
					model = this->pPlayer->getInventory()->removeCube(id);
					if (model != nullptr)
					{
						this->pPlayer->getWand()->resetPickupTimer();
						this->pPlayer->getWand()->setInPickupAnimation(true);

						XMMATRIX pWorld;
						for (auto var : this->m_LabyrinthPedestals)
						{

							if (id == var->getID())
							{
								pWorld = var->getWorld();
								break;
							}
						}
						XMVECTOR vec;
						XMVECTOR dumb;
						XMMatrixDecompose(&dumb, &dumb, &vec, pWorld);

						XMMATRIX pos;
						pos = XMMatrixTranslationFromVector(vec);
						pos *= XMMatrixTranslation(0.f, 1.35f, 0.f);

						model->setWorld(pos);
						model->setOnPedistal(true);//
						this->m_LabyrinthCubes.push_back(model);
						this->putDownSound->playSound();
					}
				}
			}
			else
			{

				for (int i = 0; i < this->m_LabyrinthCubes.size(); i++)
				{
					if (this->m_LabyrinthCubes.at(i)->getID() == id)
					{
						this->pickupSound->playSound();
						model = this->m_LabyrinthCubes[i];
						this->eraseId = i;
						this->cubeIsAboutToBeErased = true;		
						this->eraseDelay.reset();
						break;
					}
				}
				this->pPlayer->getInventory()->addCube(model);
				this->pPlayer->getWand()->resetPickupTimer();
				this->pPlayer->getWand()->setInPickupAnimation(true);				
			}
			break;
		}

	}
		break;
	case CURRENT_LEVEL::TWO:
	{


	}
		break;
	case CURRENT_LEVEL::THREE:
	{



	}
		break;
	default:
		break;
	}

	
	return -1;
}
