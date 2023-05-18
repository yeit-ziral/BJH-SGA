#include "framework.h"
#include "DungreedScene.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Player>(L"Resource/Player.png", Vector2(0.1f, 0.1f));
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Update()
{
	_player->
}

void DungreedScene::Render()
{
}
