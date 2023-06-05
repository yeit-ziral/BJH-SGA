#include "framework.h"
#include "DungreedScene.h"

#include "../../Object/Dungreed/Dun_Player.h"
#include "../../Object/Dungreed/Dun_Bullet.h"
#include "../../Object/Dungreed/Dun_Monster.h"
#include "../../Object/Dungreed/Dun_Player_Advanced.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Dun_Player_Advanced>();
	_player->SetPosition(CENTER);

	_floor = make_shared<RectCollider>(Vector2((float)WIN_WIDTH, 100.0f));
	_floor->SetPosition(Vector2(CENTER.x, 50.0f));

	_monster = make_shared<Dun_Monster>();
	_monster->SetPosition(Vector2(WIN_WIDTH - 100.0f, WIN_HEIGHT - 100.0f));
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Collider_Update()
{
	_player->Collider_Update();
	_monster->Collider_Update();
	_floor->Update();
}

void DungreedScene::Update()
{
	_player->Update();
	_monster->Update();
	_player->SetFalling(!_floor->Block(_player->GetCircleCollider()));

	if (_monster->_isAlive == true)
	{
		if (_player->IsCollision_Bullets(_monster->GetCircleCollider()))
			_monster->GetAttacked(5);
	}
}

void DungreedScene::Render()
{
	_floor->Render();
	_player->Render();

	if (_monster->_isAlive == true)
		_monster->Render();
}

void DungreedScene::PostRender()
{
	ImGui::Text("mouseX : %d, mouseY : %d", (int)MOUSE_POS.x, (int)MOUSE_POS.y);
	ImGui::Text("MonsterHP : % d", (int)_monster->GetHp());
}
