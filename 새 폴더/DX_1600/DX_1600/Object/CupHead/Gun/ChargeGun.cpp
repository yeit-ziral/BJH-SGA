#include "framework.h"
#include "ChargeGun.h"
#include "ChargingBullet.h"
#include "ChargingEffect.h"

ChargeGun::ChargeGun()
{
	CreateAction(L"Resource/CupHead/weapon/SunLord.png", "Resource/CupHead/weapon/SunLord.xml", "ChargeGun", Vector2(23,9), true);
	_gunTrans = make_shared<Transform>();
	_gunTrans->SetScale({ 5,5 });
	_atkSpeed = 0.001f;

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<ChargingBullet> bullet = make_shared<ChargingBullet>();
		_Cbullets.push_back(bullet);
	}

	//_chargingEffect = make_shared<ChargingEffect>();
	//_chargingEffect->SetParent(_gunTrans);
	//_chargingEffect->SetPosition(Vector2(12, 0));

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

	//_chargingEffect->Render();
}

void ChargeGun::PostRender()
{
	ImGui::Text("ChargingCount = %f", _chargingCount);
}

void ChargeGun::Charge()
{
	_chargingCount += DELTA_TIME;
}

void ChargeGun::Fire()
{
	if (_selected == false)
		return;

	if (_chargingCount < 1)
		return;

	SOUND->Play("Cup_Attack", 0.3f);

	auto bulletIter = std::find_if(_Cbullets.begin(), _Cbullets.end(),
		[](const shared_ptr<ChargingBullet>& obj)-> bool {return !obj->_isActive; });

	if (bulletIter == _Cbullets.end())
		return;

	Vector2 dir = MOUSE_POS - _collider->GetTransform()->GetWorldPosition();

	(*bulletIter)->Shoot(Vector2(dir.x, dir.y), _gunTrans->GetWorldPosition());
}
