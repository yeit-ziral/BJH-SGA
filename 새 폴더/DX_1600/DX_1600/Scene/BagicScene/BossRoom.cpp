#include "framework.h"
#include "BossRoom.h"
#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Monster/Cup_Boss.h"
#include "../../Object/CupHead/Cup_Track.h"
#include "../../Object/CupHead/Cup_Block.h"

BossRoom::BossRoom()
{
	_player = make_shared<Cup_Player>();
	_player->SetPosition(Vector2(0, 0));

	_track = make_shared<Cup_Track>();
	Vector2 trackSize = _track->GetTrackSize();

	//_block = make_shared<Cup_Block>(track2WorldPos + Vector2(100, 300));

	_monster = make_shared<Cup_Boss>();
	_monster->SetPosition(Vector2(0, 0));

	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(Vector2((trackSize.x * -0.5f), -1000.0f));
	//float track2PosX = _track2->GetColider()->GetTransform()->GetWorldPosition().x;
	//CAMERA->SetRightTop(Vector2(track2PosX + trackSize.x, 1000.0f));
	shared_ptr<SRV> srv = ADD_SRV(L"Resource/UI/Button.png");
	_button = make_shared<Button>(L"Resource/UI/Button.png", Vector2(96, 48));
	_button->SetPosition(Vector2(0, 0));
	_button->SetEvent(std::bind(&BossRoom::Load, this));

	Load();

	_player->SetHP(_player->GetMaxHp());
}

BossRoom::~BossRoom()
{
}

void BossRoom::Init()
{
}

void BossRoom::End()
{
}

void BossRoom::Update()
{
}

void BossRoom::Render()
{
}

void BossRoom::PostRender()
{
}

void BossRoom::CheckAttack()
{
}

void BossRoom::Save()
{
}

void BossRoom::Load()
{
}
