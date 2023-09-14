#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/CupHead/Player/Cup_Player.h"
#include "../../Object/CupHead/Monster/Cup_Monster.h"
#include "../../Object/CupHead/Monster/RoamingMonster.h"
#include "../../Object/CupHead/Cup_Track.h"
#include "../../Object/CupHead/Cup_Block.h"
#include "../../Object/CupHead/Potal.h"
#include "../../Object/CupHead/Items/RandomBox.h"

CupHeadScene::CupHeadScene()
{
	_monster = make_shared<Cup_Monster>();
	_monster->SetPosition(Vector2(100, 0));

	_monster1 = make_shared<Cup_Monster>();
	_monster1->SetPosition(Vector2(500, 0));


	_rMonster = make_shared<RoamingMonster>();
	_rMonster->SetPosition(Vector2(900, 0));

	//_monsterR = make_shared<RoamingMonster>();
	//_monsterR->SetPosition(Vector2(1000, 0));
	//_monsterR->GetTransform()->SetPosition(Vector2(0, 0));

	_track = make_shared<Cup_Track>();

	_track2 = make_shared<Cup_Track>();

	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));

	Vector2 trackSize = _track->GetTrackSize();
	float track2PosX = _track2->GetCollider()->GetTransform()->GetWorldPosition().x;

	Vector2 track2WorldPos = _track2->GetCollider()->GetTransform()->GetWorldPosition();
	_track2->SetPosition(track2WorldPos + Vector2(trackSize.x, 150.0f));

	_block = make_shared<Cup_Block>(track2WorldPos + Vector2(100, 300));


	shared_ptr<SRV> srv = ADD_SRV(L"Resource/UI/Button.png");
	_button = make_shared<Button>(L"Resource/UI/Button.png", Vector2(96, 48));

	_button->SetPosition(Vector2(WIN_WIDTH * 0.5f - 70.0f, WIN_HEIGHT * 0.5f - 24.0f));
	_button->SetEvent(std::bind(&CupHeadScene::Load, this));


	_potal = make_shared<Potal>();
	_potal = make_shared<Potal>();
	_potal->SetPosition(Vector2(-100.0f, 0.0f));

	_hpBar = make_shared<HPBar>(L"Resource/UI/Button.png", Vector2(500, 50));
	_gunHpBar = make_shared<HPBar>(L"Resource/UI/Bar.png", Vector2(500, 50));

	_potal->_isActive = false;

	_randomBox = make_shared<RandomBox>();
	_randomBox->GetTransform()->SetPosition(Vector2(-300, 0));

	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Init()
{
	Vector2 trackSize = _track->GetTrackSize();

	PLAYER->SetPosition(Vector2(0, 20));

	PLAYER->SetJumpPower(0.0f);

	if (_monster->_isAlive == false && _monster1->_isAlive ==false && _rMonster->_isAlive == false)
	{
		_monster->~Cup_Monster();
		_monster1->~Cup_Monster();

		_monster = make_shared<Cup_Monster>();
		_monster->SetPosition(Vector2(100, 0));
		_monster->_isAlive = true;

		_monster1 = make_shared<Cup_Monster>();
		_monster1->SetPosition(Vector2(500, 0));
		_monster1->_isAlive = true;

		//_monster->SetPosition(Vector2(0, 0));
		//_monster->ResetHp();
		//_monster->_isAlive = true;

		//
		_rMonster = make_shared<RoamingMonster>();
		_rMonster->SetPosition(Vector2(900, 0));
		_rMonster->_isAlive = true;
		//
	}



	CAMERA->SetTarget(PLAYER->GetTransform());
	CAMERA->SetLeftBottom(Vector2((trackSize.x * -0.5f), -1000.0f));
	float track2PosX = _track2->GetCollider()->GetTransform()->GetWorldPosition().x;
	CAMERA->SetRightTop(Vector2(track2PosX + trackSize.x, 1000.0f));

	_randomBox->SetRandomItem();
	_randomBox->_isActive = false;

	//Load();
}

void CupHeadScene::End()
{
	Save();
	// CupHead 총알회수
}

void CupHeadScene::Update()
{
	_track->Update();
	_track2->Update();
	_block->Update();

	PLAYER->Update();

	_button->Update();

	_potal->Update();

	_hpBar->Update();
	
	_gunHpBar->Update();

	if (_monster->_isAlive == false && _monster1->_isAlive == false && _rMonster->_isAlive == false)
		_potal->_isActive = true;

	if (_track->GetCollider()->Block(PLAYER->GetFootCollider()))
	{
		if (_track->GetCollider()->_sideCollision)
			return;

		PLAYER->SetGrounded();
	}
	if (_track2->GetCollider()->Block(PLAYER->GetFootCollider()))
	{
		if (_track2->GetCollider()->_sideCollision)
			return;

		PLAYER->SetGrounded();
	}

	if (KEY_PRESS('S'))
	{

	}
	else
	{
		if (_block->GetCollider()->IsCollision(PLAYER->GetFootCollider()))
		{
			if(_block->GetCollider()->_bottomCollision)
			{ }
			else
			{
				if (_block->GetCollider()->Block(PLAYER->GetFootCollider()))
				{
					PLAYER->SetGrounded();
					//if (PLAYER->GetJumpPower() > 0.0f)
					//	PLAYER->SetJumpPower(0.0f);
				}
			}
		}
		
	}

	if (_block->GetCollider()->Block(_monster->GetCollider()))
	{

	}
	if (_track->GetCollider()->Block(_monster1->GetCollider()))
	{

	}
	if (_track2->GetCollider()->Block(_rMonster->GetCollider()))
	{

	}

	Vector2 playerpos = PLAYER->GetTransform()->GetWorldPosition();

	_monster->Update(playerpos);
	_monster1->Update(playerpos);
	//_monsterR->Update(playerpos);
	//
	_rMonster->Update(PLAYER->GetCollider());
	//

	// 몬스터가 일정 거리 안에서만 공격
	Vector2 bosspos = _monster->GetTransform()->GetWorldPosition();
	int distance = playerpos.Distance(bosspos);
	if (distance < 500.0f) // 이 거리는 일반몹에 적합
		_monster->Attack(PLAYER->GetCollider()->GetTransform()->GetWorldPosition());

	Vector2 bossposR = _monster1->GetTransform()->GetWorldPosition();
	int distanceR = playerpos.Distance(bossposR);
	if (distanceR < 500.0f) 
		_monster1->Attack(PLAYER->GetCollider()->GetTransform()->GetWorldPosition());


	CheckAttack();


	_hpBar->SetMaxHp(PLAYER->GetMaxHp());
	_hpBar->SetCurHp(PLAYER->GetHp());
	Vector2 a = _hpBar->GetXSizeHalf();

	_hpBar->SetPosition(Vector2(a.x - WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f - a.y));

	if (_potal->IsCollision(PLAYER->GetCollider()) && _monster->_isAlive == false && _monster1->_isAlive == false)
	{
		_potal->_isActive = false;
		SceneManager::GetInstance()->NextScene();
	}

	_gunHpBar->SetMaxHp(PLAYER->GetGunMaxHp());
	_gunHpBar->SetCurHp(PLAYER->GetGunHp());
	Vector2 b = _gunHpBar->GetXSizeHalf();

	_gunHpBar->SetPosition(Vector2(b.x - WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f - a.y - (b.y * 2.0f)));

	if (!_monster->_isAlive && !_monster1->_isAlive)
		_randomBox->_isActive = true;

	if (_randomBox->_isActive)
	{
		_randomBox->Update();
		_randomBox->IsCollision(PLAYER);
	}

	if (KEY_DOWN(VK_LBUTTON))
	{
		EFFECT_PLAY("Hit", MOUSE_POS);
	}


	if (!PLAYER->_isAlive)
		SceneManager::GetInstance()->LobbyScene();
}

void CupHeadScene::Render()
{
	_track->Render();
	_track2->Render();
	_block->Render();

	if (_potal->_isActive == true)
		_potal->Render();

	PLAYER->Render();

	if (_monster->_isAlive == true)
		_monster->Render();

	if (_monster1->_isAlive == true)
		_monster1->Render();

	if (_rMonster->_isAlive)
		_rMonster->Render();

	if (!_monster->_isAlive && !_monster1->_isAlive && !_rMonster->_isAlive)
		_randomBox->Render();
}

void CupHeadScene::PostRender()
{
	PLAYER->PostRender();
	_monster->PostRender();
	_monster1->PostRender();

	//ImGui::Text("MousePositionX : % d", (int)W_MOUSE_POS.x);
	//ImGui::Text("MousePositionY : % d", (int)W_MOUSE_POS.y);
	//ImGui::Text("MonsterHP : % d", (int)_monster->GetHp());
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

	ImGui::Text("RandomBosPos : %f, %f", _randomBox->GetTransform()->GetWorldPosition().x, _randomBox->GetTransform()->GetWorldPosition().y);
}

void CupHeadScene::CheckAttack()
{
	if (_monster->_isAlive && PLAYER->GetHp() > 0)
	{
		if (_monster->IsCollsion_Bullets(PLAYER->GetCollider()))
		{

			PLAYER->Damaged(_monster->GetDamage());
		}

		if (PLAYER->IsCollision_Bullets(_monster->GetCollider()))
		{
			_monster->GetAttacked(PLAYER->GetNowGunDamage());
		}
	}

	if (_monster1->_isAlive && PLAYER->GetHp() > 0)
	{

		if (PLAYER->IsCollision_Bullets(_monster1->GetCollider()))
		{
			EFFECT_PLAY("Hit", _monster->GetTransform()->GetWorldPosition());
			_monster1->GetAttacked(PLAYER->GetNowGunDamage());
		}



		if (_monster1->IsCollsion_Bullets(PLAYER->GetCollider()))
		{
			EFFECT_PLAY("Hit", _monster1->GetTransform()->GetWorldPosition());
			PLAYER->Damaged(_monster1->GetDamage());
		}
	}



}

void CupHeadScene::Save()
{
	BinaryWriter writer = BinaryWriter(L"Save/test.test");
	writer.Int(1);

	Vector2 playerPos = PLAYER->GetCollider()->GetTransform()->GetWorldPosition();

	writer.String("PlayerPos");
	writer.Byte(&playerPos, sizeof(Vector2));

	int playerHP = PLAYER->GetHp();

	writer.String("PlayerHP");
	writer.Byte(&playerHP, sizeof(int));
}

void CupHeadScene::Load()
{
	BinaryReader reader = BinaryReader(L"Save/test.test");
	int temp = reader.Int();

	string str = reader.String();
	assert(str == "PlayerPos");

	Vector2 playerPos;
	Vector2* ptr = &playerPos;
	reader.Byte((void**)&ptr, sizeof(Vector2));

	PLAYER->SetPosition(playerPos);

	string strhp = reader.String();
	assert(strhp == "PlayerHP");

	int playerHP;
	int* php = &playerHP;
	reader.Byte((void**)&php, sizeof(int));

	PLAYER->SetHp(playerHP);
}
