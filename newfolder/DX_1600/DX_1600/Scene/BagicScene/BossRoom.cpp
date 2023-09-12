#include "framework.h"
#include "BossRoom.h"
#include "../../Object/CupHead/Player/Cup_Player.h"
#include "../../Object/CupHead/Monster/Cup_Boss.h"
#include "../../Object/CupHead/Cup_Wall.h"
#include "../../Object/CupHead/Cup_Track.h"
#include "../../Object/CupHead/Potal.h"

BossRoom::BossRoom()
{
	//_player = make_shared<Cup_Player>();


	_track = make_shared<Cup_Track>();


	_wall = make_shared<Cup_Wall>();

	


	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));



	shared_ptr<SRV> srv = ADD_SRV(L"Resource/UI/Button.png");
	_button = make_shared<Button>(L"Resource/UI/Button.png", Vector2(96, 48));
	_button->SetPosition(Vector2(WIN_WIDTH * 0.5f - 70.0f, WIN_HEIGHT * 0.5f - 24.0f));
	_button->SetEvent(std::bind(&BossRoom::Load, this));

	Vector2 trackSize = _track->GetTrackSize();

	_potal = make_shared<Potal>();
	_potal->SetPosition(Vector2(100.0f, 0.0f));

	//_player->SetHP(_player->GetMaxHp());

	_hpBar = make_shared<HPBar>(L"Resource/UI/Button.png", Vector2(500, 50));
	_gunHpBar = make_shared<HPBar>(L"Resource/UI/Bar.png", Vector2(500, 50));

	Load();
}

BossRoom::~BossRoom()
{
}

void BossRoom::Init()
{
	PLAYER->SetPosition(Vector2(-200, 0));
	PLAYER->SetJumpPower(0.0f);

	_boss = make_shared<Cup_Boss>();
	_boss->GetCollider()->SetPosition(Vector2(200.0f, 0.0f));

	Vector2 trackSize = _track->GetTrackSize();

	CAMERA->SetTarget(PLAYER->GetTransform());
	CAMERA->SetLeftBottom(Vector2((-trackSize.x * 0.125f), -100.0f));
	CAMERA->SetRightTop(Vector2((trackSize.x), 1000.0f));

	Load();
}

void BossRoom::End()
{
}

void BossRoom::Update()
{
	PLAYER->Update();
	_boss->Update(PLAYER->GetTransform()->GetWorldPosition());
	_track->Update();
	_wall->Update();
	_button->Update();
	_potal->Update();
	_hpBar->Update();
	_gunHpBar->Update();

	if (_boss->_isAlive == false)
		_potal->_isActive = true;

	if (_wall->GetUpWall()->Block(_boss->GetCollider()) && PLAYER->_isAlive == true)
	{
		//_boss->Fire(_player->GetCollider()->GetPos());
	}

	if (_track->GetCollider()->Block(PLAYER->GetFootCollider()))
	{
		if (_track->GetCollider()->_sideCollision)
			return;

		PLAYER->SetGrounded();
	}
	if (_track->GetCollider()->Block(_boss->GetCollider()))
	{
		if (_track->GetCollider()->_sideCollision)
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
		if (PLAYER->IsCollision_Bullets(_boss->GetCollider()))
		{
			if (PLAYER->GetNowGun() == Cup_Player::Gun::MACHINE)
				_boss->Damage(1);
			if (PLAYER->GetNowGun() == Cup_Player::Gun::NORMAL)
				_boss->Damage(5);
			if (PLAYER->GetNowGun() == Cup_Player::Gun::CHARGE)
				_boss->Damage(15);
		}

		if (_boss->IsCollsion_Bullets(PLAYER->GetCollider()) && PLAYER->_isAlive)
		{
			PLAYER->Damaged(_boss->GetDamage());
			//_player->SetHit(true);
		}

		if (_boss->IsDash())
		{
			if(PLAYER->GetCollider()->IsCollision(_boss->GetCollider()) && PLAYER->_isAlive)
			{
				PLAYER->Damaged(_boss->GetDashDamage());
			}
		}
	}



	_hpBar->SetMaxHp(PLAYER->GetMaxHp());
	_hpBar->SetCurHp(PLAYER->GetHp());
	Vector2 a = _hpBar->GetXSizeHalf();

	_hpBar->SetPosition(Vector2(a.x - WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f - a.y));

	_gunHpBar->SetMaxHp(PLAYER->GetGunMaxHp());
	_gunHpBar->SetCurHp(PLAYER->GetGunHp());
	Vector2 b = _gunHpBar->GetXSizeHalf();

	_gunHpBar->SetPosition(Vector2(b.x - WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f - a.y - (b.y * 2.0f)));

	if (_potal->IsCollision(PLAYER->GetCollider()) && _boss->_isAlive == false)
	{
		_potal->_isActive = false;
		SceneManager::GetInstance()->NextScene();
	}

	if (!PLAYER->_isAlive)
		SceneManager::GetInstance()->LobbyScene();
}

void BossRoom::Render()
{
	_track->Render();
	_wall->Render();

	_potal->Render();

	PLAYER->Render();

	if (_boss->_isAlive == true)
		_boss->Render();
}

void BossRoom::PostRender()
{
	PLAYER->PostRender();
	_boss->PostRender();

	ImGui::Text("MousePositionX : % d", (int)W_MOUSE_POS.x);
	ImGui::Text("MousePositionY : % d", (int)W_MOUSE_POS.y);
	ImGui::Text("MonsterHP : % d", (int)_boss->GetHp());
	ImGui::Text("PlayerHP : % d", (int)PLAYER->GetHp());

	if (ImGui::Button("TargetON", ImVec2(50, 50)))
	{
		CAMERA->SetTarget(PLAYER->GetTransform());
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

	_hpBar->PostRender();
	_gunHpBar->PostRender();
}

void BossRoom::CheckAttack()
{
	if (!_boss->_isAlive || !PLAYER->_isAlive)
		return;

	if (PLAYER->IsCollision_Bullets(_boss->GetCollider()))
	{
		_boss->GetAttacked(PLAYER->GetNowGunDamage());
	}

	if (_boss->IsCollsion_Bullets(PLAYER->GetCollider()))
	{
		PLAYER->Damaged(1);
		//_player->SetHit(true);
	}
}

void BossRoom::Save()
{
}

void BossRoom::Load()
{
}
