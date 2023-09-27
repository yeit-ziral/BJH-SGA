#include "framework.h"
#include "RoamingMonster.h"
#include "../Gun/Bullets/Cup_Bullet.h"

RoamingMonster::RoamingMonster()
{
	_monster = make_shared<CircleCollider>(50);

	_transform = make_shared<Transform>();
	_transform->SetParent(_monster->GetTransform());

	_monsterQuad = make_shared<Quad>(L"Resource/BoomMonster.png");

	_isAlive = true;

	srand(static_cast<unsigned int>(time(nullptr)));
}

RoamingMonster::~RoamingMonster()
{
}

void RoamingMonster::Update(shared_ptr<Collider> collider)
{
	if (!_isAlive)
		return;

	if (_hp <= 0)
		_isAlive = false;

	{
		_jumpPower -= 1000.0f * DELTA_TIME;

		if (_jumpPower < -600.0f)
			_jumpPower = -600.0f;

		_monster->GetTransform()->AddVector2(Vector2(0.0f, 1.0f) * _jumpPower * DELTA_TIME);
	}

	_monster->Update();

	_transform->Update();

	_time += DELTA_TIME;

	int a = (_monster->GetTransform()->GetWorldPosition()).Distance(collider->GetTransform()->GetWorldPosition());

	if (a < 300.0f)
	{
		Attack(collider); // 돌진해서 자폭
	}
	else
	{
		if (_time > 2.0f)
		{
			Roaming();
			if (_time > 5.0f)
			{
				_time = 0.0f;

				movingDir = RandomNum(-1, 2);
			}
		}
	}
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
	//ImGui::Text("R-monsterPos : %f, %f", _monster->GetPos().x, _monster->GetPos().y);
	//ImGui::Text("R-monsterHp : %d", _hp);
}

void RoamingMonster::Attack(shared_ptr<Collider> collider)
{
	_atkTime += DELTA_TIME;

	float dir = collider->GetTransform()->GetWorldPosition().x - _monster->GetTransform()->GetWorldPosition().x;

	if (_atkTime > 3.0f)
	{
		_hp = 0;
		EFFECT_PLAY("Exp2", _monster->GetTransform()->GetWorldPosition());
		_time = 0.0f;
	}

	if (dir > 0)
	{
		SetRight();
		Vector2 movePos = Vector2(+_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}
	if (dir < 0)
	{
		SetLeft();
		Vector2 movePos = Vector2(-_speed, 0.0f) * DELTA_TIME;
		Move(movePos);
	}
	if (collider->IsCollision(_monster))
	{
		_hp = 0;
		EFFECT_PLAY("Exp2", _monster->GetTransform()->GetWorldPosition());
		_time = 0.0f;
		_isAlive = false;
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
		EFFECT_PLAY("Exp2", _monster->GetTransform()->GetWorldPosition());
		_isAlive = false;
	}
}

void RoamingMonster::Roaming()
{
	if (movingDir > 0)
	{
		SetRight();
		Vector2 movePos = Vector2(_speed * 0.1f, 0.0f) * DELTA_TIME;
		Move(movePos);
	}
	if (movingDir < 0)
	{
		SetLeft();
		Vector2 movePos = Vector2(_speed * -0.1f, 0.0f) * DELTA_TIME;
		Move(movePos);
	}

}

void RoamingMonster::SetLeft()
{
	if (_isRight)
	{
		_monsterQuad->FlipVertically();
		_isRight = false;
	}
}

void RoamingMonster::SetRight()
{
	if (!_isRight)
	{
		_monsterQuad->FlipVertically();
		_isRight = true;
	}
}
