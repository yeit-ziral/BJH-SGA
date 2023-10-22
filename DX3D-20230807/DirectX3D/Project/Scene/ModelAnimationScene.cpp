#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	zombie = new Zombie();
	//groot = new Groot();
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete zombie;
	//delete groot;
}

void ModelAnimationScene::Update()
{
	zombie->Update();
	//groot->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	zombie->Render();
	//groot->Render();
}

void ModelAnimationScene::PostRender()
{
	zombie->Debug();
	//groot->Debug();
}
