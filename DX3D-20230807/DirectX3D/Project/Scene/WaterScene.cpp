#include "Framework.h"
#include "WaterScene.h"

WaterScene::WaterScene()
{
	CreateObjects();

	reflection = new Reflection(floor);

	sky = new SkyBox(L"Landscape/Snow_ENV.dds");

	floor->GetMaterial()->SetShader(L"19Reflection");
}

WaterScene::~WaterScene()
{
	delete floor;
	delete groot;
	delete bunny;
	delete sphere;
	delete sky;
}

void WaterScene::Update()
{
	reflection->Update();

	floor->Update();
	groot->Update();
	bunny->Update();
	sphere->Update();
}

void WaterScene::PreRender()
{
	reflection->SetPreRender(); // sky보다 위에 있어야지 sky도 반사 됨

	sky->Render();

	//floor->Render();
	groot->Render();
	bunny->Render();
	sphere->Render();
}

void WaterScene::Render()
{
	sky->Render();

	reflection->SetRender();

	floor->Render();
	groot->Render();
	bunny->Render();
	sphere->Render();
}

void WaterScene::PostRender()
{
	reflection->PostRender();

	Environment::GetInstance()->PostRender();
}

void WaterScene::CreateObjects()
{
	floor = new Quad();
	floor->SetLabel("Floor");

	floor->rotation.x = XM_PIDIV2;
	floor->scale *= 100.0f;

	floor->translation.y = 1.0f;

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
