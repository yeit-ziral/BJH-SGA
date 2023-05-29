#include "framework.h"
#include "Dun_Monster.h"

Dun_Monster::Dun_Monster()
{
	_quad = make_shared<Quad>(L"Resource/Goomba.png");
	float a = _quad->GetTransform()->GetWorldScale().x * 0.5f;
	_monster = make_shared<CircleCollider>(50);
	_monster->GetTransform()->SetPosition(Vector2(500.0f, WIN_HEIGHT * 0.5f));

	_hp = 10;
}

Dun_Monster::~Dun_Monster()
{
}

void Dun_Monster::Update()
{
	_quad->GetTransform()->SetPosition(_monster->GetTransform()->GetWorldPosition());

	_monster->Update();
	_quad->Update();
}

void Dun_Monster::Render()
{
	if (_isAlive == true)
	{
		_monster->Render();
		_quad->Render();
	}
}
