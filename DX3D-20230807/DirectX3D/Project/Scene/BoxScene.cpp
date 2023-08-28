#include "Framework.h"
#include "BoxScene.h"

BoxScene::BoxScene()
{
	box = new Box2();
}

BoxScene::~BoxScene()
{
	delete box;
}

void BoxScene::Update()
{
	box->Update();
}

void BoxScene::PreRender()
{
}

void BoxScene::Render()
{
	box->Render();
}

void BoxScene::PostRender()
{
}
