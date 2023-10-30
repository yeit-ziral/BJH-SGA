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

	crosshair = new Quad();
	crosshair->GetMaterial()->SetDiffuseMap(L"UI/CrossHair.png");
	crosshair->GetMaterial()->SetShader(L"Texture");
	crosshair->scale = { 200, 200, 1 };
}

ModelAnimationScene::~ModelAnimationScene()
{
	//delete zombie;
	delete groot;

	delete  terrain;

	delete crosshair;
}

void ModelAnimationScene::Update()
{
	//zombie->Update();
	groot->Update();

	terrain->Update();

	groot->translation.y = terrain->GetHeight(groot->GetGlobalPosition());

	crosshair->translation.x = mousePos.x;
	crosshair->translation.y = WIN_HEIGHT - mousePos.y;

	crosshair->Update();
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

	StateManager::GetInstance()->AlphaBegin();

	crosshair->Render();

	StateManager::GetInstance()->AlphaEnd();

	terrain->Debug();
}