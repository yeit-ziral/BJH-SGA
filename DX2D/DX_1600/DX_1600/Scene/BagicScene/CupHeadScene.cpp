#include "framework.h"
#include "CupHeadScene.h"
#include "../../Object/CupHead/Cup_Player.h"
#include "../../Object/CupHead/Cup_Monster.h"

CupHeadScene::CupHeadScene()
{
	_player = make_shared<Cup_Player>();
	_player->SetPosition(CENTER);

	_track = make_shared<Quad>(L"Resource/CupHead/clown_bg_track.png");
	_transform = make_shared<Transform>();
	Vector2 trackSize = _track->GetQuadHalfSize();
	_col = make_shared<RectCollider>(trackSize * 2.0f);

	_transform->SetParent(_col->GetTransform());
	_transform->SetPosition(Vector2(0, 75));

	Vector2 pos = CENTER;
	pos.y -= 300.0f;
	_col->GetTransform()->SetPosition(pos);

	_monster = make_shared<Cup_Monster>();
	_monster->SetPosition(Vector2(WIN_WIDTH - 100.0f, WIN_HEIGHT - 100.0f));
}

CupHeadScene::~CupHeadScene()
{
}

void CupHeadScene::Update()
{
	_player->Update();

	_transform->Update();
	_col->Update();

	if (_col->Block(_player->GetCollider()))
		_player->SetGrounded();

	_monster->Update();

	if (_monster->_isAlive == true)
	{
		if (_player->IsCollision_Bullets(_monster->GetCircleCollider()))
			_monster->GetAttacked(5);
	}
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

	ImGui::Text("MonsterHP : % d", (int)_monster->GetHp());
}
