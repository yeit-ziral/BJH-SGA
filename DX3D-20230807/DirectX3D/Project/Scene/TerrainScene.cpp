#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap.png");

	//terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	terrain->GetMaterial()->SetSpecularMap(L"Landscape/Fieldstone_SM.tga");

	sphere = new Sphere();
}

TerrainScene::~TerrainScene()
{
	delete terrain;
}

void TerrainScene::Update()
{
	terrain->Update();

	sphere->Update();
}

void TerrainScene::PreRender()
{
}

void TerrainScene::Render()
{
	terrain->Render();

	sphere->Render();
}

void TerrainScene::PostRender()
{
	terrain->GetMaterial()->PostRender();
}
