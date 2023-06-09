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

	if (KEY_PRESS(VK_LBUTTON))
	{
		Charge();
	}

	if (KEY_UP(VK_LBUTTON))
	{
		SOUND->Play("Cup_Attack", 0.3f);

		// ���콺 �������� �Ѿ� ���
		Fire();

	}
}

void ChargeGun::Render()
{
	_gun->Render();
}

void ChargeGun::Charge()
{
	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<Cup_Bullet>& obj)-> bool {return !obj->_isActive; });

	if (bulletIter == _bullets.end())
		return;

	float beforeSize = (*bulletIter)->GetBulletCollider()->GetRadius();

	(*bulletIter)->GetBulletCollider()->SetScale(beforeSize + 1);
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
