#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	//zombie = new Zombie();
	groot = new Groot();

	groot->scale *= 0.1;

	terrain = new Terrain(L"LandScape/Dirt.png", L"HeightMap/Heightmap.png");
}

ModelAnimationScene::~ModelAnimationScene()
{
	//delete zombie;
	delete groot;

	delete  terrain;
}

void ModelAnimationScene::Update()
{
	//zombie->Update();
	groot->Update();

	terrain->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	//zombie->Render();
	groot->Render();

	terrain->Render();
}

void ModelAnimationScene::PostRender()
{
	//zombie->Debug();
	groot->Debug();

	terrain->Debug();
}