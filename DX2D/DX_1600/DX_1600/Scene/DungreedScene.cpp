#include "framework.h"
#include "DungreedScene.h"

#include "../Object/Dungreed/Dun_Player.h"
#include "../Object/Dungreed/Dun_Bullet.h"
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
	if (_monster->_isAlive == true)
		_monster->Update();

	_ground->GetGroundCollider()->Block(_player->GetCircleCollider());

	for (auto bullet : _player->GetBullet())
	{
		if (bullet->GetBulletCollider()->IsCollision(_monster->GetCircleCollider()))
		{
			bullet->_isActive = false;

			_monster->GetAttacked();
		}
	}
}

void DungreedScene::Render()
{
	_player->Render();
	_ground->Render();
	if (_monster->_isAlive == true)
		_monster->Render();
}

void DungreedScene::PostRender()
{
	ImGui::Text("mouseX : %d, mouseY : %d", (int)MOUSE_POS.x, (int)MOUSE_POS.y);
	ImGui::Text("MonsterHP : %d", (int)_monster->GetHp());
}
