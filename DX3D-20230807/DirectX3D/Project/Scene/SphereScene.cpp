#include "Framework.h"
#include "SphereScene.h"

SphereScene::SphereScene()
{
	sphere = new Sphere();
}

SphereScene::~SphereScene()
{
}

void SphereScene::Update()
{
	sphere->Update();
}

void SphereScene::PreRender()
{
}

void SphereScene::Render()
{
	sphere->Render();
}

void SphereScene::PostRender()
{
}
