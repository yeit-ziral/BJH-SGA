#include "framework.h"
#include "Lobby.h"
#include "../../Object/CupHead/Player/Cup_Player.h"
#include "../../Object/CupHead/Cup_Track.h"
#include "../../Object/CupHead/Potal.h"
#include "../../Object/UI/HPBar.h"
#include "../../Object/UI/inventory.h"
#include "../../Object/CupHead/Items/Helmet.h"
#include "../../Object/CupHead/Items/KingBullet.h"
#include "../../Object/CupHead/Items/HpPotion.h"
#include "../../Object/CupHead/Items/FixingTool.h"

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

	//_inven = make_shared<inventory>();
	//_inven->GetTransform()->SetPosition(PLAYER->GetTransform()->GetWorldPosition());

	_helmet = make_shared<Helmet>();
	_helmet->GetTransform()->SetPosition(Vector2(100, 0));
	_helmet->_isActivated = true;

	_kingBullet = make_shared<KingBullet>();
	_kingBullet->GetTransform()->SetPosition(Vector2(-100, 0));
	_kingBullet->_isActivated = true;

	_hpPotion = make_shared<HpPotion>();
	_hpPotion->GetTransform()->SetPosition(Vector2(-200, 0));
	_hpPotion->_isActivated = true;

	_fixingTool = make_shared<FixingTool>();
	_fixingTool->GetTransform()->SetPosition(Vector2(-300, 0));
	_fixingTool->_isActivated = true;
}

Lobby::~Lobby()
{
}

void Lobby::Init()
{
	PLAYER->SetPosition(Vector2(0, 0));
	PLAYER->SetJumpPower(0.0f);

	Vector2 trackSize = _track->GetTrackSize();

	//CAMERA->SetTarget(PLAYER->GetTransform());
	//CAMERA->SetLeftBottom(Vector2((-trackSize.x * 0.125f), -100.0f));
	//CAMERA->SetRightTop(Vector2((trackSize.x), 1000.0f));

	//CAMERA->SetTarget(PLAYER->GetTransform());
	CAMERA->SetLeftBottom(Vector2(0.0f, 0.0f));
	CAMERA->SetRightTop(Vector2(trackSize.x - 200.0f, 1000.0f));

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

	 if (_track->GetColider()->Block(PLAYER->GetFootCollider()))
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


	 _helmet->Update();

	 if (_helmet->GetCollider()->IsCollision(PLAYER->GetCollider()) && _helmet->_isActivated)
	 {
		 //if (!_helmet->_isActivated)
			// return;
		
		 _helmet->_isActivated = false;
		 PLAYER->FillItem(Cup_Player::Item::HELMET);
	 }

	 _kingBullet->Update();

	 if (_kingBullet->GetCollider()->IsCollision(PLAYER->GetCollider()) && _kingBullet->_isActivated)
	 {
		 _kingBullet->_isActivated = false;
		 PLAYER->FillItem(Cup_Player::Item::KINGBULLET);
	 }

	 _hpPotion->Update();
	 if (_hpPotion->GetCollider()->IsCollision(PLAYER->GetCollider()) && _hpPotion->_isActivated)
	 {
		 _hpPotion->_isActivated = false;
		 PLAYER->AddHP(5);
	 }

	 _fixingTool->Update();
	 if (_fixingTool->GetCollider()->IsCollision(PLAYER->GetCollider()) && _fixingTool->_isActivated)
	 {
		 _fixingTool->_isActivated = false;
		 PLAYER->FixGun(15);
	 }


	 if (_potal->IsCollision(PLAYER->GetCollider()))
		 SceneManager::GetInstance()->NextScene();
}

void Lobby::Render()
{
	 _potal->Render();
	 _track->Render();
	 _helmet->Render();
	 _kingBullet->Render();
	 _hpPotion->Render();
	 _fixingTool->Render();

	 PLAYER->Render();

	// 다른 Scene에서는 PostRender에 넣을것
	_hpBar->PostRender(); 
	_gunHpBar->PostRender();
	
	
	//_inven->PostRender();
}

void Lobby::Save()
{
}

void Lobby::Load()
{
}
