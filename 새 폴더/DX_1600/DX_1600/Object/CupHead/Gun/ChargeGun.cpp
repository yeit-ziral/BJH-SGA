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

	// bullet을 ChargingBullet으로 바꿔야 됨
	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<ChargingBullet>& obj)-> bool {return !obj->_isActive; });

	if (bulletIter == _bullets.end())
		return;

	Vector2 dir = MOUSE_POS - _collider->GetTransform()->GetWorldPosition();

	if (KEY_PRESS(VK_LBUTTON))
	{
		// 총알 크기와 데미지 증가
		(*bulletIter)
	}

	if (KEY_UP(VK_LBUTTON))
	{
		// 발사 후 크기와 데미지 원래대로 복귀
		(*bulletIter)->Shoot(Vector2(dir.x, dir.y), _collider->GetTransform()->GetWorldPosition());
	}

	_atkCool = true;

}
