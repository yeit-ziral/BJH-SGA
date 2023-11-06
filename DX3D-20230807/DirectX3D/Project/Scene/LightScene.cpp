#include "Framework.h"
#include "LightScene.h"

LightScene::LightScene()
{
	floor = new Quad();
	floor->SetLabel("Floor");
	floor->rotation.x = XM_PIDIV2;
	floor->scale *= 100.0f;
	floor->translation.y += 1;
	floor->GetMaterial()->SetShader(L"09Light");

	groot = new Groot();
	groot->GetReader()->SetShader(L"09Light");

	bunny = new Model("StanfordBunny");
	bunny->SetLabel("StanfordBunny");
	bunny->scale *= 0.05f;
	bunny->translation = { -30, 12, 0 };
	bunny->GetReader()->SetShader(L"09Light");

	sphere = new Sphere();
	sphere->scale *= 5.0f;
	sphere->translation = { 30,20,0 };
	sphere->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetNormalMap(L"Landscape/fieldstone_NM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"Landscape/fieldstone_SM.tga");
	sphere->GetMaterial()->SetShader(L"09Light");
}

LightScene::~LightScene()
{
	delete floor;
	delete groot;
	delete bunny;
	delete sphere;
}

void LightScene::Update()
{
	floor ->Update();
	groot ->Update();
	bunny ->Update();
	sphere->Update();
}

void LightScene::PreRender()
{
}

void LightScene::Render()
{
	floor ->Render();
	groot ->Render();
	bunny ->Render();
	sphere->Render();
}

void LightScene::PostRender()
{
	floor ->Debug();
	groot ->Debug();
	bunny ->GetReader()->Debug();
	sphere->Debug();
}
