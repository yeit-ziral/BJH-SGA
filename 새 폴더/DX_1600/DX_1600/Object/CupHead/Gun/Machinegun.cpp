#include "framework.h"
#include "Machinegun.h"
#include "../Cup_Bullet.h"

Machinegun::Machinegun()
{
	_gun = make_shared<Quad>(L"Resource/CupHead/weapon/rifle.png");
}

Machinegun::~Machinegun()
{
}

void Machinegun::Update()
{
}

void Machinegun::Render()
{
	_gun->Render();
}

void Machinegun::Fire()
{
	if (_atkCool)
	{
		_time += DELTA_TIME;
		if (_time > _atkSpeed)
		{
			_time = 0.0f;
			_atkCool = false;
		}
		return;
	}

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<Cup_Bullet>& obj)-> bool {return !obj->_isActive; });

	if (bulletIter == _bullets.end())
		return;

	Vector2 dir = MOUSE_POS - _collider->GetTransform()->GetWorldPosition();

	(*bulletIter)->Shoot(Vector2(dir.x, dir.y), _collider->GetTransform()->GetWorldPosition());

	_atkCool = true;

}
