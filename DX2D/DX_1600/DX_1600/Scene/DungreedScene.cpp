#include "framework.h"
#include "DungreedScene.h"

#include "../Object/Dungreed/Dun_Player.h"
#include "../Object/Dungreed/Dun_Ground.h"
#include "../Object/Dungreed/Dun_Monster.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Dun_Player>();
	_ground = make_shared<Dun_Ground>();
	_monster = make_shared<Dun_Monster>();
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Update()
{
	if(KEY_PRESS('A'))
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
	_ground->Update();
	_monster->Update();

	if (_ground->GetGroundCollider()->Block(_player->GetCircleCollider()))
		_ground->GetGroundCollider()->SetRed();

	/*auto it = find_if(_player->GetBullet().begin(), _player->GetBullet().end(), []()-> bool
		{

		});*/
}

void DungreedScene::Render()
{
	_player->Render();
	_ground->Render();
	_monster->Render();
}

void DungreedScene::PostRender()
{
	ImGui::Text("mouseX : %d, mouseY : %d", (int)MOUSE_POS.x, (int)MOUSE_POS.y);
}
