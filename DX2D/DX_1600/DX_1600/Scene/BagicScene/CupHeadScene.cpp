#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Cup_Monster.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Player>();
	_player->SetPosition(Vector2(0,0));

	_track = make_shared<Quad>(L"Resource/CupHead/clown_bg_track.png");
	_transform = make_shared<Transform>();
	Vector2 trackSize = _track->GetQuadHalfSize();
	_col = make_shared<RectCollider>(trackSize * 2.0f);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 75));

	Vector2 pos = CENTER;
	pos.y -= 300.0f;
	_col->GetTransform()->SetPosition(Vector2(0.0f, CENTER.y * -1));
	_transform->Update();

	_monster = make_shared<Cup_Monster>();
	_monster->SetPosition(Vector2(0, 0));

	EffectManager::GetInstance()->AddEffect("Hit", L"Resource/explosion.png", Vector2(5, 3), Vector2(150, 150));

	CAMERA->SetTarget(_player->GetTransform());
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();

	_col->Update();

	if (_col->Block(_player->GetCollider()))
		_player->SetGrounded();

	_monster->Update();
	_monster->Attack(_player->GetCollider()->GetTransform()->GetWorldPosition());
	CheckAttack();
}

void CupHeadScene::Render()
{
	_transform->SetBuffer(0);
	_track->Render();
	_col->Render();

	_player->Render();

	if (_monster->_isAlive == true)
		_monster->Render();
}

void CupHeadScene::PostRender()
{
	_player->PostRender();
	_monster->PostRender();

	ImGui::Text("MonsterHP : % d", (int)_monster->GetHp());
	ImGui::Text("PlayerHP : % d", (int)_player->GetHp());

	//ImGui::SliderInt("Selected", &_AFBuffer->_data.selected, 0, 10);
	//ImGui::SliderInt("value1", &_AFBuffer->_data.value1, 1, 300);
	//ImGui::SliderInt("value2", &_AFBuffer->_data.value2, 0, 300);
	//ImGui::SliderInt("value3", &_AFBuffer->_data.value3, 0, 300);
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
		_player->Attacked(1);
		_player->SetHit(true);
	}
}
