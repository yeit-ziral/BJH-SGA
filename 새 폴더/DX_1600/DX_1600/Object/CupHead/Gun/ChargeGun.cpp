#include "framework.h"
#include "ChargeGun.h"
#include "ChargingBullet.h"

ChargeGun::ChargeGun()
{
	CreateAction(L"Resource/CupHead/weapon/SunLord.png", "Resource/CupHead/weapon/SunLord.xml", "ChargeGun", Vector2(23,9), true);
	_gunTrans = make_shared<Transform>();
	_gunTrans->SetScale({ 5,5 });
	_atkSpeed = 0.01f;

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<ChargingBullet> bullet = make_shared<ChargingBullet>();
		_Cbullets.push_back(bullet);
	}

	_damage = 0;
}

ChargeGun::~ChargeGun()
{
}

void ChargeGun::Update()
{
	if (_selected == false)
		return;

	_gunTrans->Update();

	if (MOUSE_POS.x < 0)
	{
		SetLeft();
		_gunTrans->SetAngle(-PI);
	}
	if (MOUSE_POS.x > 0)
	{
		SetRight();
		_gunTrans->SetAngle(0);
	}

	_action->Update();
	_gun->Update();

	for (auto bullet : _Cbullets)
		bullet->Update();
}

void ChargeGun::Render()
{
	if (_selected == false)
		return;

	_gunTrans->SetBuffer(0);
	_gun->SetCurClip(_action->GetCurClip());
	_gun->Render();

	for (auto bullet : _Cbullets)
		bullet->Render();
}

void ChargeGun::Charge()
{
	_chargingCount += 1;
}

void ChargeGun::Fire() // charging�̶� �ƴҶ� �и��ϱ�
{
	if (_selected == false)
		return;

	if (_chargingCount < 10)
		return;

	SOUND->Play("Cup_Attack", 0.3f);

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

	auto bulletIter = std::find_if(_Cbullets.begin(), _Cbullets.end(),
		[](const shared_ptr<ChargingBullet>& obj)-> bool {return !obj->_isActive; });

	if (bulletIter == _Cbullets.end())
		return;

	Vector2 dir = MOUSE_POS - _collider->GetTransform()->GetWorldPosition();

	(*bulletIter)->Shoot(Vector2(dir.x, dir.y), _gunTrans->GetWorldPosition());

	_atkCool = true;

}
