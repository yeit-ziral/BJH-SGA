#include "framework.h"
#include "ChargeGun.h"
#include "../Cup_Bullet.h"

ChargeGun::ChargeGun()
{
	_gun = make_shared<Quad>(L"Resource/CupHead/weapon/SunLord.png");
}

ChargeGun::~ChargeGun()
{
}

void ChargeGun::Update()
{
}

void ChargeGun::Render()
{
	_gun->Render();
}

void ChargeGun::Fire()
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
