#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	terrainEditor = new TerrainEditor(200, 200);
	terrainEditor->GetMaterial()->SetDiffuseMap (L"LandScape/Fieldstone_DM.tga");
	terrainEditor->GetMaterial()->SetSpecularMap(L"LandScape/fieldstone_SM.tga");
	terrainEditor->GetMaterial()->SetNormalMap  (L"LandScape/fieldstone_NM.tga");
}

TerrainEditorScene::~TerrainEditorScene()
{
	delete terrainEditor;
}

void TerrainEditorScene::Update()
{
	terrainEditor->Update();

	if (KEY_DOWN(VK_LBUTTON))
		terrainEditor->Picking(&pickedPos);

	Vector3 a = Vector3(1, 1, 1);

}

void TerrainEditorScene::PreRender()
{
}

void TerrainEditorScene::Render()
{
	terrainEditor->Render();
}

void TerrainEditorScene::PostRender()
{
	terrainEditor->Debug();

	ImGui::Text("PickedPos : %.1f, %.1f,%.1f", pickedPos.x, pickedPos.y, pickedPos.z);
}
