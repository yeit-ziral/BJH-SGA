#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Monster/Cup_Monster.h"
#include "../../Object/CupHead/Cup_Track.h"
#include "../../Object/CupHead/Cup_Block.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Player>();
	_player->SetPosition(Vector2(0,0));

	_track = make_shared<Cup_Track>();
	Vector2 trackSize = _track->GetTrackSize();

	_track2 = make_shared<Cup_Track>();
	Vector2 track2WorldPos = _track2->GetColider()->GetTransform()->GetWorldPosition();
	_track2->SetPosition(track2WorldPos + Vector2(trackSize.x, 150.0f));

	_block = make_shared<Cup_Block>(track2WorldPos + Vector2(100, 300));

	_monster = make_shared<Cup_Monster>();
	_monster->SetPosition(Vector2(0, 0));

	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(Vector2((trackSize.x * -0.5f), -1000.0f));
	float track2PosX = _track2->GetColider()->GetTransform()->GetWorldPosition().x;
	CAMERA->SetRightTop(Vector2(track2PosX + trackSize.x, 1000.0f));
	shared_ptr<SRV> srv = ADD_SRV(L"Resource/UI/Button.png");
	_button = make_shared<Button>(L"Resource/UI/Button.png", Vector2(96, 48));
	_button->SetPosition(Vector2(0,0));
	_button->SetEvent(std::bind(&CupHeadScene::Load, this));

	Load();

	_player->SetHP(_player->GetMaxHp());
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Init()
{
	Load();
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

	_player->Update();

	_button->Update();

	if (_track->GetColider()->Block(_player->GetCollider()))
	{
		if (_track->GetColider()->_sideCollision)
			return;

		_player->SetGrounded();
	}
	if (_track2->GetColider()->Block(_player->GetCollider()))
	{
		if (_track2->GetColider()->_sideCollision)
			return;

		_player->SetGrounded();
	}

	if (KEY_PRESS(VK_DOWN))
	{

	}
	else
	{
		if (_block->GetCollider()->Block(_player->GetCollider()));
		_player->SetGrounded();
		if (_block->GetCollider()->_bottomCollision)
		{

		}
		else
		{

		}
	}

	Vector2 playerpos = _player->GetTransform()->GetWorldPosition();

	_monster->Update(playerpos);

	// 보스가 일정 거리 안에서만 공격
	Vector2 bosspos = _monster->GetTransform()->GetWorldPosition();
	int distance = playerpos.Distance(bosspos);
	if (distance < 500.0f) // 이 거리는 일반몹에 적합
		_monster->Attack(_player->GetCollider()->GetTransform()->GetWorldPosition());
	CheckAttack();
}

void CupHeadScene::Render()
{
	_track->Render();
	_track2->Render();
	_block->Render();

	_player->Render();

	if (_monster->_isAlive == true)
		_monster->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
	_monster->PostRender();

	ImGui::Text("MousePositionX : % d", (int)W_MOUSE_POS.x);
	ImGui::Text("MousePositionY : % d", (int)W_MOUSE_POS.y);
	ImGui::Text("MonsterHP : % d", (int)_monster->GetHp());
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

void CupHeadScene::CheckAttack()
{
	if (!_monster->_isAlive || !_player->_isAlive)
		return;

	if (_player->IsCollision_Bullets(_monster->GetCollider()))
	{
		_monster->GetAttacked(5);
	}

	if (_monster->IsCollsion_Bullets(_player->GetCollider()))
	{
		_player->Damaged(1);
		//_player->SetHit(true);
	}
}

void CupHeadScene::Save()
{
	BinaryWriter writer = BinaryWriter(L"Save/test.test");
	writer.Int(1);

	Vector2 playerPos = _player->GetCollider()->GetTransform()->GetWorldPosition();

	writer.String("PlayerPos");
	writer.Byte(&playerPos, sizeof(Vector2));

	int playerHP = _player->GetHp();

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

	_player->SetPosition(playerPos);

	string strhp = reader.String();
	assert(strhp == "PlayerHP");

	int playerHP;
	int* php = &playerHP;
	reader.Byte((void**)&php, sizeof(int));

	_player->SetHP(playerHP);
}
