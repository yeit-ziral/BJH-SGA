#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	quad = new Quad();
	quad2 = new Quad();

	quad->translation.x += 0.5;
	quad->rotation.x += 0.01;
}

TextureScene::~TextureScene()
{
	delete quad;
	delete quad2;
}

void TextureScene::Update()
{
	quad->Update();
	quad2->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	quad->Render();
	quad2->Render();
}

void TextureScene::PostRender()
{
}
