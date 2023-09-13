#include "framework.h"
#include "RoamingMonster.h"
#include "../Gun/Bullets/Cup_Bullet.h"
using namespace tinyxml2;

RoamingMonster::RoamingMonster()
{
	_monster = make_shared<CircleCollider>(150);

	_monsterQuad = make_shared<Quad>(L"Resource/Player.png");

	_transform = make_shared<Transform>();
	_transform->SetParent(_monster->GetTransform());
	
	//활 대신 창, 창은 각도 바꾸지 않음
}

RoamingMonster::~RoamingMonster()
{
}

void RoamingMonster::Update(Vector2 targetPos)
{
	if (!_isAlive)
		return;

	if (_hp <= 0)
		_isAlive = false;

	_monster->Update();

	_transform->Update();

}

void RoamingMonster::Render()
{
	if (!_isAlive)
		return;

	_monster->Render();

	_transform->SetBuffer(0);

	_monsterQuad->Render();

}

void RoamingMonster::PostRender()
{
	ImGui::Text("R-monsterPos : %f, %f", _monster->GetPos().x, _monster->GetPos().y);
	ImGui::Text("R-monsterHp : %d", _hp);
}

void RoamingMonster::Attack(shared_ptr<Collider> collider)
{
	float dir = collider->GetTransform()->GetWorldPosition().x - _monster->GetTransform()->GetWorldPosition().x;



	if (dir > 0)
	{
		Move(Vector2(1, 0));
	}
	if (dir < 0)
	{
		Move(Vector2(-1, 0));
	}
	if (collider->IsCollision(_monster))
	{
		_hp = 0;
		EFFECT_PLAY("Hit", _monster->GetTransform()->GetWorldPosition());
	}

}

void RoamingMonster::GetAttacked(int amount)
{
	if (!_isAlive)
		return;

	_hp -= amount;

	if (_hp <= 0)
	{
		_hp = 0;
	}
}

void RoamingMonster::Roaming()
{
}

void RoamingMonster::SetLeft()
{
	_monsterQuad->FlipVertically();
}

void RoamingMonster::SetRight()
{
}
