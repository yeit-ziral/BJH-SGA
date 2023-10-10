#include "Framework.h"
#include "TerrainScene.h"

TerrainScene::TerrainScene()
{
	terrain = new Terrain(L"Landscape/Dirt.png", L"HeightMap/HeightMap.png");

	//terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	//terrain->GetMaterial()->SetSpecularMap(L"Landscape/Fieldstone_SM.tga");

	// normalMap 추가하기
	//terrain->GetMaterial()->SetNormalMap(L"Landscape/fieldsone_NM.tga");

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

	if (KEY_DOWN(VK_LBUTTON))
	{
		terrain->Picking(&pickedPos);

		sphere->translation = pickedPos;
		sphere->translation.y += sphere->scale.y;
	}
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
	terrain->GetMaterial()->Debug();

	ImGui::Text("PickedPos : %.1f, %.1f,%.1f", pickedPos.x, pickedPos.y, pickedPos.z);
}
