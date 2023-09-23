#include "framework.h"
#include "ChargeGun.h"
#include "Bullets/ChargingBullet.h"
#include "ChargingEffect.h"

ChargeGun::ChargeGun()
{
	CreateAction(L"Resource/CupHead/weapon/SunLord.png", "Resource/CupHead/weapon/SunLord.xml", "ChargeGun", Vector2(23,9), true);
	_gunTrans = make_shared<Transform>();
	_gunTrans->SetScale({ 5,5 });
	_atkSpeed = 0.001f;

	_chargeEffect = make_shared<Sprite>(L"Resource/chargingEffect/chargingEffect.png", "Resource/chargingEffect/chargingEffect.xml", Vector2(40, 40));

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<ChargingBullet> bullet = make_shared<ChargingBullet>();
		_Cbullets.push_back(bullet);
	}

	//_chargingEffect = make_shared<ChargingEffect>();
	//_chargingEffect->SetParent(_gunTrans);
	//_chargingEffect->SetPosition(Vector2(12, 0));

	_damage = 20;
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

	//_chargingEffect->Update();
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

	if (_isCharging)
		_chargeEffect->Render();
}

void ChargeGun::PostRender()
{
	ImGui::Text("ChargingCount = %f", _chargingCount);
}

void ChargeGun::Charge()
{
	_isCharging = true;
	_chargingCount += DELTA_TIME;

	if (_chargingCount < 0.125f)
	{
		_chargeEffect->SetCurClip(0);
		_chargeEffect->Update();
	}
	if (_chargingCount > 0.125 && _chargingCount < 0.25f)
	{
		_chargeEffect->SetCurClip(1);
		_chargeEffect->Update();
	}
	if (_chargingCount > 0.25f && _chargingCount < 0.375f)
	{
		_chargeEffect->SetCurClip(2);
		_chargeEffect->Update();
	}
	if (_chargingCount > 0.375f && _chargingCount < 0.5f)
	{
		_chargeEffect->SetCurClip(3);
		_chargeEffect->Update();
	}
	if (_chargingCount > 0.5f && _chargingCount < 0.625f)
	{
		_chargeEffect->SetCurClip(4);
		_chargeEffect->Update();
	}
	if (_chargingCount > 0.625f && _chargingCount < 0.75f)
	{
		_chargeEffect->SetCurClip(5);
		_chargeEffect->Update();
	}
	if (_chargingCount > 0.75f && _chargingCount < 0.875f)
	{
		_chargeEffect->SetCurClip(6);
		_chargeEffect->Update();
	}
	if (_chargingCount > 0.875f && _chargingCount < 1.0f)
	{
		_chargeEffect->SetCurClip(7);
		_chargeEffect->Update();
	}
}

void ChargeGun::Fire(Vector2 dir)
{
	if (_selected == false)
		return;

	if (_chargingCount < 1)
		return;

	if (_hp <= 0)
		return;

	SOUND->Play("Cup_Attack", 0.3f);

	auto bulletIter = std::find_if(_Cbullets.begin(), _Cbullets.end(),
		[](const shared_ptr<ChargingBullet>& obj)-> bool {return !obj->_isActive; });

	if (bulletIter == _Cbullets.end())
		return;

	//Vector2 dir = W_MOUSE_POS - _collider->GetTransform()->GetWorldPosition();

	(*bulletIter)->Shoot(Vector2(dir.x, dir.y), _gunTrans->GetWorldPosition());

	_hp -= 20;

	if (_hp <= 0)
		_hp = 0;
}

bool ChargeGun::IsCollision_CBullet(shared_ptr<Collider> col)
{
	for (auto bullet : _Cbullets)
	{
		if (bullet->_isActive == false)
			continue;

		if (col->IsCollision(bullet->GetBulletCollider()))
		{
			bullet->_isActive = false;
			EFFECT_PLAY("Hit", bullet->GetPosition());
			return true;
		}
	}

	return false;
}
