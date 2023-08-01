#include "framework.h"
#include "BossRoom.h"
#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Monster/Cup_Boss.h"
#include "../../Object/CupHead/Cup_Wall.h"
#include "../../Object/CupHead/Cup_Track.h"

BossRoom::BossRoom()
{
	_player = make_shared<Cup_Player>();
	_player->SetPosition(Vector2(0, 0));

	_track = make_shared<Cup_Track>();
	Vector2 trackSize = _track->GetTrackSize();

	_wall = make_shared<Cup_Wall>();

	_boss = make_shared<Cup_Boss>();
	_boss->SetPosition(Vector2(0, 0));

	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));

	CAMERA->SetTarget(_player->GetTransform());
	CAMERA->SetLeftBottom(Vector2((trackSize.x * -0.5f), -1000.0f));

	shared_ptr<SRV> srv = ADD_SRV(L"Resource/UI/Button.png");
	_button = make_shared<Button>(L"Resource/UI/Button.png", Vector2(96, 48));
	_button->SetPosition(Vector2(0, 0));
	_button->SetEvent(std::bind(&BossRoom::Load, this));

	Load();

	_player->SetHP(_player->GetMaxHp());

#pragma region RTV
	_rtv = make_shared<RenderTarget>();
	_rtvQuad = make_shared<Quad>(Vector2(WIN_WIDTH, WIN_HEIGHT));
	_rtvQuad->SetSRV(_rtv->GetSRV());
	_rtvQuad->SetPS(ADD_PS(L"Shader/FilterPS.hlsl"));

	_rtvTransform = make_shared<Transform>();
	_filterbuffer = make_shared<FilterBuffer>();
	_filterbuffer->_data.selected = 1;

#pragma endregion
}

BossRoom::~BossRoom()
{
}

void BossRoom::Init()
{
	Load();
}

void BossRoom::End()
{
}

void BossRoom::Update()
{
	_player->Update();
	_boss->Update();
	_track->Update();
	_wall->Update();
	_button->Update();

	_rtvTransform->Update();
	_filterbuffer->Update();

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
		if (_player->isCollision_Bullets(_boss->GetCollider()))
		{
			_boss->Damage(1);
		}
	}


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
