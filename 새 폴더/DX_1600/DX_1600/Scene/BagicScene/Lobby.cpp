#include "framework.h"
#include "Lobby.h"
#include "../../Object/CupHead/Player/Cup_Player.h"
#include "../../Object/CupHead/Cup_Track.h"
#include "../../Object/CupHead/Potal.h"
#include "../../Object/UI/HPBar.h"

Lobby::Lobby()
{
	//_player = make_shared<Cup_Player>();


	_track = make_shared<Cup_Track>();
	Vector2 trackSize = _track->GetTrackSize();

	_potal = make_shared<Potal>();
	_potal->SetPosition(Vector2(200.0f, 0.0f));
	_potal->_isActive = true;

	_hpBar = make_shared<HPBar>(L"Resource/UI/Button.png", Vector2(500, 50));
	_gunHpBar = make_shared<HPBar>(L"Resource/UI/Bar.png", Vector2(500, 50));

	PLAYER->SetPosition(Vector2(0, 0));
}

Lobby::~Lobby()
{
}

void Lobby::Init()
{
	PLAYER->SetPosition(Vector2(0, 0));
	PLAYER->SetJumpPower(0.0f);

	Vector2 trackSize = _track->GetTrackSize();

	CAMERA->SetTarget(PLAYER->GetTransform());
	//CAMERA->SetLeftBottom(Vector2((-trackSize.x * 0.125f), -100.0f));
	//CAMERA->SetRightTop(Vector2((trackSize.x), 1000.0f));

	Load();
}

void Lobby::End()
{
}

void Lobby::Update()
{
	PLAYER->Update();
	 _track->Update();
	 _potal->Update();
	 _hpBar->Update();
	 _gunHpBar->Update();

	 if (_track->GetColider()->Block(PLAYER->GetCollider()))
	 {
		 if (_track->GetColider()->_sideCollision)
			 return;

		 PLAYER->SetGrounded();
	 }

	 _hpBar->SetMaxHp(PLAYER->GetMaxHp());
	 _hpBar->SetCurHp(PLAYER->GetHp());
	 Vector2 a = _hpBar->GetXSizeHalf();

	 _hpBar->SetPosition(Vector2(a.x - WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f - a.y));

	 _gunHpBar->SetMaxHp(PLAYER->GetGunMaxHp());
	 _gunHpBar->SetCurHp(PLAYER->GetGunHp());
	 Vector2 b = _gunHpBar->GetXSizeHalf();

	 _gunHpBar->SetPosition(Vector2(b.x - WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f - a.y - (b.y * 2.0f)));



	 if (_potal->IsCollision(PLAYER->GetCollider()))
		 SceneManager::GetInstance()->NextScene();
}

void Lobby::Render()
{
	 _potal->Render();
	 _track->Render();
	 PLAYER->Render();

	// 다른 Scene에서는 PostRender에 넣을것
	_hpBar->PostRender(); 
	_gunHpBar->PostRender();
}

void Lobby::Save()
{
}

void Lobby::Load()
{
}
