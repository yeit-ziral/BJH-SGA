#include "framework.h"
#include "Dun_Monster.h"

Dun_Monster::Dun_Monster()
{
	_quad = make_shared<Quad>(L"Resource/Goomba.png");
	_transform = make_shared<Transform>();
	_monster = make_shared<CircleCollider>(_quad->GetQuadHalfSize().x);

	_transform->SetParent(_monster->GetTransform());
	_monster->GetTransform()->SetScale(Vector2(0.5f, 0.5f));
}

Dun_Monster::~Dun_Monster()
{
}

void Dun_Monster::Collider_Update()
{
	if (!_isAlive)
		return;
	_monster->Update();
}

void Dun_Monster::Update()
{
	if (!_isAlive)
		return;
	_transform->Update();
}

void Dun_Monster::Render()
{
	if (!_isAlive)
		return;

	_transform->SetBuffer(0);
	_monster->Render();
	_quad->Render();
}

void Dun_Monster::GetAttacked(int amount)
{
	if (!_isAlive)
		return;
	_hp -= amount;

	if (_hp <= 0)
	{
		_isAlive = false;
		_hp = 0;
	}
}
