#include "framework.h"
#include "BossRoom.h"
#include "../../Object/CupHead/Player/Cup_Player.h"
#include "../../Object/CupHead/Monster/Cup_Boss.h"
#include "../../Object/CupHead/Cup_Wall.h"
#include "../../Object/CupHead/Cup_Track.h"
#include "../../Object/CupHead/Potal.h"

BossRoom::BossRoom()
{
	_player = make_shared<Cup_Player>();


	_track = make_shared<Cup_Track>();


	_wall = make_shared<Cup_Wall>();

	_boss = make_shared<Cup_Boss>();


	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));



	shared_ptr<SRV> srv = ADD_SRV(L"Resource/UI/Button.png");
	_button = make_shared<Button>(L"Resource/UI/Button.png", Vector2(96, 48));
	_button->SetPosition(Vector2(0, 0));
	_button->SetEvent(std::bind(&BossRoom::Load, this));

	Vector2 trackSize = _track->GetTrackSize();

	_potal = make_shared<Potal>();
	_potal->SetPosition(Vector2(100.0f, 0.0f));

	Load();

	_player->SetHP(_player->GetMaxHp());

}

BossRoom::~BossRoom()
{
}

void BossRoom::Init()
{
	//if (_boss->_isAlive == false)
	//{

	//	_boss->SetPosition(Vector2(0, 0));
	//	_boss->ResetHp();
	//	_boss->_isAlive = true;
	//}
	// 
	_player->SetPosition(Vector2(0, 0));

	Vector2 trackSize = _track->GetTrackSize();

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(Vector2((-trackSize.x * 0.125f), -100.0f));
	CAMERA->SetRightTop(Vector2((trackSize.x), 1000.0f));

	Load();
}

void BossRoom::End()
{
}

void BossRoom::Update()
{
	_player->Update();
	_boss->Update(_player->GetTransform()->GetWorldPosition());
	_track->Update();
	_wall->Update();
	_button->Update();
	_potal->Update();

	if (_boss->_isAlive == false)
		_potal->_isActive = true;

	if (_wall->GetUpWall()->Block(_boss->GetCollider()) && _player->_isAlive == true)
	{
		//_boss->Fire(_player->GetCollider()->GetPos());
	}

	if (_track->GetColider()->Block(_player->GetCollider()))
	{
		if (_track->GetColider()->_sideCollision)
			return;

		_player->SetGrounded();
	}
	if (_track->GetColider()->Block(_boss->GetCollider()))
	{
		if (_track->GetColider()->_sideCollision)
			return;
	}

	if (_boss->GetCollider()->IsCollision(_wall->GetLeftWall()))
	{
		_boss->_isWallCrash = true;
		_boss->GetCollider()->GetTransform()->AddVector2(Vector2(100, 0));
	}

	if (_boss->GetCollider()->IsCollision(_wall->GetRightWall()))
	{
		_boss->_isWallCrash = true;
		_boss->GetCollider()->GetTransform()->AddVector2(Vector2(-100, 0));
	}

	if (_boss->_isAlive == true)
	{
		if (_player->IsCollision_Bullets(_boss->GetCollider()))
		{
			if (_player->GetNowGun() == Cup_Player::Gun::MACHINE)
				_boss->Damage(1);
			if (_player->GetNowGun() == Cup_Player::Gun::NORMAL)
				_boss->Damage(5);
			if (_player->GetNowGun() == Cup_Player::Gun::CHARGE)
				_boss->Damage(15);
		}
	}

	if (_boss->IsCollsion_Bullets(_player->GetCollider()))
	{
		_player->Attacked(1);
		//_player->SetHit(true);
	}

	if (_potal->IsCollision(_player->GetCollider()))
		SceneManager::GetInstance()->NextScene();
}

void BossRoom::Render()
{
	_track->Render();
	_wall->Render();

	_potal->Render();

	_player->Render();

	if (_boss->_isAlive == true)
		_boss->Render();
}

void BossRoom::PostRender()
{
	_player->PostRender();
	_boss->PostRender();

	ImGui::Text("MousePositionX : % d", (int)W_MOUSE_POS.x);
	ImGui::Text("MousePositionY : % d", (int)W_MOUSE_POS.y);
	ImGui::Text("MonsterHP : % d", (int)_boss->GetHp());
	ImGui::Text("PlayerHP : % d", (int)_player->GetHp());

	if (ImGui::Button("TargetON", ImVec2(50, 50)))
	{
		CAMERA->SetTarget(_player->GetTransform());
	}

	if (ImGui::Button("TargetOFF", ImVec2(50, 50)))
	{
		CAMERA->SetTarget(nullptr);
	}

	if (ImGui::Button("Save", ImVec2(50, 50)))
	{
		Save();
	}

	if (ImGui::Button("Load", ImVec2(50, 50)))
	{
		Load();
	}

	_button->PostRender();
}

void BossRoom::CheckAttack()
{
	if (!_boss->_isAlive || !_player->_isAlive)
		return;

	if (_player->IsCollision_Bullets(_boss->GetCollider()))
	{
		_boss->GetAttacked(5);
	}

	if (_boss->IsCollsion_Bullets(_player->GetCollider()))
	{
		_player->Damaged(1);
		//_player->SetHit(true);
	}
}

void BossRoom::Save()
{
}

void BossRoom::Load()
{
}
