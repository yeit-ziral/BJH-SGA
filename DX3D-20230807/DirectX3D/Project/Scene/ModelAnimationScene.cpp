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

	sky = new SkyBox(L"Landscape/SpaceBox.dds");
}

ModelAnimationScene::~ModelAnimationScene()
{
	//delete zombie;
	delete groot;

	delete  terrain;

	delete crosshair;

	delete sky;
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
	sky->Render();
	//zombie->Render();
	groot->Render();

	terrain->Render();

}

void ModelAnimationScene::PostRender()
{
	//StateManager::GetInstance()->AlphaBegin();

	crosshair->Render();

	//StateManager::GetInstance()->AlphaEnd();

	terrain->Debug();
	groot->PostRender();

	//sky->PostRender();
}