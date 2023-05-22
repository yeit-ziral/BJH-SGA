#include "framework.h"
#include "DungreedScene.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Player>();

}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Update()
{
	if (KEY_PRESS('A'))
	{
		Vector2 movePos = Vector2(-500.0f, 0.0f) * DELTA_TIME;
		_player->Move(movePos);
	}

	if (KEY_PRESS('D'))
	{
		Vector2 movePos = Vector2(500.0f, 0.0f) * DELTA_TIME;
		_player->Move(movePos);
	}

	_player->Update();
}

void DungreedScene::Render()
{
	_player->Render();
}
