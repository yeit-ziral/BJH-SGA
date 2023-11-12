#include "Framework.h"
#include "LightScene.h"

LightScene::LightScene()
{
	CreateObjects();

	renderTarget = new RenderTarget();
	depthStencil = new DepthStencil();

	Texture* texture = Texture::Get(L"RenderTarget", renderTarget->GetSRV());

	floor->GetMaterial()->SetDiffuseMap(texture);
	floor2->GetMaterial()->SetDiffuseMap(texture);

	buffer = new FloatValueBuffer();
}

LightScene::~LightScene()
{
	delete floor;
	delete floor2;
	delete groot;
	delete bunny;
	delete sphere;

	delete renderTarget;
	delete depthStencil;

	delete buffer;
}

void LightScene::Update()
{
	floor ->Update();
	floor2->Update();
	groot ->Update();
	bunny ->Update();
	sphere->Update();
}

void LightScene::PreRender()
{
	renderTarget->Set(depthStencil, Vector4(1, 1, 0, 1));

	groot->Render();
	bunny->Render();
	sphere->Render();
}

void LightScene::Render()
{

}

void LightScene::PostRender()
{
	buffer->SetPSBuffer(10);

	floor ->Render();
	floor2->Render();

	const char* list[] = { "Mosaic", "Blur", "RadialBlur" };

	ImGui::Combo("Type", (int*)&buffer->data.values[0], list, 3);

	ImGui::SliderFloat("Scale1", &buffer->data.values[1], 1, 700);
	ImGui::SliderFloat("Scale2", &buffer->data.values[2], 1, 100);
	ImGui::SliderFloat("Scale3", &buffer->data.values[3], 1, 700);

	//floor ->Debug();
	//floor2->Debug();
	//groot ->Debug();
	//bunny ->GetReader()->Debug();
	sphere->GetMaterial()->Debug();
}

void LightScene::CreateObjects()
{
	floor = new Quad();
	floor->SetLabel("Floor");
	//floor->rotation.x = XM_PIDIV2;
	//floor->scale *= 100.0f;
	//floor->translation.y += 1;
	floor->scale.x = WIN_WIDTH  * 0.5f;
	floor->scale.y = WIN_HEIGHT * 0.5f;

	floor->translation.x = WIN_WIDTH  * 0.25f;
	floor->translation.y = WIN_HEIGHT * 0.25f;

	floor->GetMaterial()->SetShader(L"11PostEffect");

	floor2= new Quad();
	floor2->SetLabel("Floor2");

	floor2->scale.x = WIN_WIDTH * 0.5f;
	floor2->scale.y = WIN_HEIGHT * 0.5f;
		 
	floor2->translation.x = WIN_WIDTH * 0.75f;
	floor2->translation.y = WIN_HEIGHT * 0.75f;
		 
	floor2->GetMaterial()->SetShader(L"10GrayScale");

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
