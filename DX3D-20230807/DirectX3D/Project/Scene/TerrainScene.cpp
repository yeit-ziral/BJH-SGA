#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap.png");



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
}
