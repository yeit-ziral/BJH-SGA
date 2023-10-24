#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	//zombie = new Zombie();
	groot = new Groot();

	groot->scale *= 0.05;

	terrain = new Terrain(L"LandScape/Dirt.png", L"HeightMap/Heightmap.png");

	terrain->scale *= 2.5;

	Camera::GetInstance()->SetTarget(groot);
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

	groot->translation.y = terrain->GetHeight(groot->GetGlobalPosition());
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