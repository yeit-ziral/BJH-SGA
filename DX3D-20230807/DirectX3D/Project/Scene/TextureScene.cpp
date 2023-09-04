#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	cube = new TextureCube();
	cube->SetLabel("Cube");

	CAMERA->translation = { 0, 3, -5 };

	cube2 = new Cube({ 1,0,0,1 });
	cube2->translation.x = 2;
}

TextureScene::~TextureScene()
{
	delete cube;
}

void TextureScene::Update()
{
	cube->Update();
	cube2->Update();

	cube->rotation.x += Time::Delta();
	cube2->rotation.x += Time::Delta();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	cube->Render();
	cube2->Render();
}

void TextureScene::PostRender()
{
	cube->Debug();
	//cube2->Debug();
}
