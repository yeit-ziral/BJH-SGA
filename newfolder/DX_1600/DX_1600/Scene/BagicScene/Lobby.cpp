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
#include "../../Object/CupHead/Items/Scope.h"
#include "../../Object/CupHead/Items/SpeedBoots.h"
#include "../../Object/CupHead/Items/RandomBox.h"
#include "../../Object/CupHead/Monster/RoamingMonster.h"
////////////

Lobby::Lobby()
{
	PLAYER->SetPosition(Vector2(0, 0));

	_backGroundTransform = make_shared<Transform>();

	_backGround = make_shared<Quad>(L"Resource/BackGround.png");




	_track = make_shared<Cup_Track>();
	Vector2 trackSize = _track->GetTrackSize();

	_potal = make_shared<Potal>();
	_potal->SetPosition(Vector2(200.0f, 0.0f));
	_potal->_isActive = true;

	_hpBar = make_shared<HPBar>(L"Resource/UI/Button.png", Vector2(500, 50));
	_gunHpBar = make_shared<HPBar>(L"Resource/UI/Bar.png", Vector2(500, 50));

	PLAYER->SetPosition(Vector2(0, 0));

	_helmet = make_shared<Helmet>();
	_helmet->GetTransform()->SetPosition(Vector2(-100, 50));
	_helmet->_isActivated = true;

	_speedBoots = make_shared<SpeedBoots>();
	_speedBoots->GetTransform()->SetPosition(Vector2(-100, 0));
	_speedBoots->_isActivated = true;

	_kingBullet = make_shared<KingBullet>();
	_kingBullet->GetTransform()->SetPosition(Vector2(-300, 50));
	_kingBullet->_isActivated = true;

	_scope = make_shared<Scope>();
	_scope->GetTransform()->SetPosition(Vector2(-200, 50));
	_scope->_isActivated = true;

	_hpPotion = make_shared<HpPotion>();
	_hpPotion->GetTransform()->SetPosition(Vector2(-200, 0));
	_hpPotion->_isActivated = true;

	_fixingTool = make_shared<FixingTool>();
	_fixingTool->GetTransform()->SetPosition(Vector2(-300, 0));
	_fixingTool->_isActivated = true;

	_randomBox = make_shared<RandomBox>();
	_randomBox->GetTransform()->SetPosition(Vector2(100, 0));
	_randomBox->SetRandomItem();
	_randomBox->_isActive = true;



	/// <summary>
	/// //////////////////////////////////////////
	/// </summary>

}

Lobby::~Lobby()
{
}

void Lobby::Init()
{
	//if (!PLAYER->_isAlive)
	PLAYER->Revive();

	while (PLAYER->GetItemState() != Cup_Player::Item::NONE) // 인벤 첫 칸이 NONE일 때 까지
	{
		PLAYER->DropItem();
	}

	PLAYER->SetPosition(Vector2(0, 0));
	PLAYER->SetJumpPower(0.0f);

	_helmet = make_shared<Helmet>();
	_helmet->GetTransform()->SetPosition(Vector2(100, 0));
	_helmet->_isActivated = true;

	_speedBoots = make_shared<SpeedBoots>();
	_speedBoots->GetTransform()->SetPosition(Vector2(-100, 0));
	_speedBoots->_isActivated = true;

	_hpPotion = make_shared<HpPotion>();
	_hpPotion->GetTransform()->SetPosition(Vector2(-200, 0));
	_hpPotion->_isActivated = true;

	_fixingTool = make_shared<FixingTool>();
	_fixingTool->GetTransform()->SetPosition(Vector2(-300, 0));
	_fixingTool->_isActivated = true;

	_kingBullet = make_shared<KingBullet>();
	_kingBullet->GetTransform()->SetPosition(Vector2(-300, 50));
	_kingBullet->_isActivated = true;

	_scope = make_shared<Scope>();
	_scope->GetTransform()->SetPosition(Vector2(-200, 50));
	_scope->_isActivated = true;

	_randomBox = make_shared<RandomBox>();
	_randomBox->GetTransform()->SetPosition(Vector2(300, -50));
	_randomBox->SetRandomItem();
	_randomBox->_isActive = true;

	Vector2 trackSize = _track->GetTrackSize();

	//CAMERA->SetTarget(PLAYER->GetTransform());
	//CAMERA->SetLeftBottom(Vector2((-trackSize.x * 0.125f), -100.0f));
	//CAMERA->SetRightTop(Vector2((trackSize.x), 1000.0f));

	//CAMERA->SetTarget(PLAYER->GetTransform());
	CAMERA->SetLeftBottom(Vector2(0.0f, 0.0f));
	CAMERA->SetRightTop(Vector2(trackSize.x - 200.0f, 1000.0f));

	_randomBox->SetRandomItem();


	Load();
}

void Lobby::End()
{
}

void Lobby::Update()
{
	_backGroundTransform->Update();

	_backGroundTransform->SetScale(Vector2(5, 5));

	PLAYER->Update();

	 _track->Update();
	 _potal->Update();
	 _hpBar->Update();
	 _gunHpBar->Update();

	 if (_track->GetCollider()->Block(PLAYER->GetFootCollider()))
	 {
		 if (_track->GetCollider()->_sideCollision)
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
	 _helmet->IsCollision(PLAYER);

	 _speedBoots->Update();
	 _speedBoots->IsCollision(PLAYER);

	 _kingBullet->Update();
	 _kingBullet->IsCollision(PLAYER);

	 _scope->Update();
	 _scope->IsCollision(PLAYER);

	 _hpPotion->Update();
	 _hpPotion->IsCollision(PLAYER);

	 _fixingTool->Update();
	 _fixingTool->IsCollision(PLAYER);

	 if (_randomBox->_isActive)
		 _randomBox->Update();

	 _randomBox->IsCollision(PLAYER);

	 if (_potal->IsCollision(PLAYER->GetCollider()))
	 {
		 _randomBox->SetItemStateNone();
		 SceneManager::GetInstance()->NextScene();
	 }

}

void Lobby::Render()
{
	_backGroundTransform->SetBuffer(0);

	_backGround->Render();

	 _potal->Render();
	 _track->Render();
	 _helmet->Render();
	 _speedBoots->Render();
	 _kingBullet->Render();
	 _scope->Render();
	 _hpPotion->Render();
	 _fixingTool->Render();

	 PLAYER->Render();


	 if (_randomBox->_isActive)
		 _randomBox->Render();

	// 다른 Scene에서는 PostRender에 넣을것
	_hpBar->PostRender(); 
	_gunHpBar->PostRender();
	
	//PLAYER->PostRender();

	//ImGui::Text("RandomBoxPos : %f, %f", _randomBox->GetTransform()->GetWorldPosition().x, _randomBox->GetTransform()->GetWorldPosition().y);

}

void Lobby::Save()
{
}

void Lobby::Load()
{
}
