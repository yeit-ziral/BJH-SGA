#include "framework.h"
#include "Machinegun.h"
#include "Bullets/Cup_Bullet.h"

Machinegun::Machinegun()
{
	CreateAction(L"Resource/CupHead/weapon/rifle.png", "Resource/CupHead/weapon/rifle.xml", "MachineGun", Vector2(22,8), true);
	_gunTrans = make_shared<Transform>();
	_gunTrans->SetScale({ 5,5 });

	_atkSpeed = 0.1f;

	_damage = 3;
}

Machinegun::~Machinegun()
{
}

void Machinegun::Update()
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

	for (auto bullet : _bullets)
		bullet->Update();
}

void Machinegun::Render()
{
	if (_selected == false)
		return;

	_gunTrans->SetBuffer(0);
	_gun->SetCurClip(_action->GetCurClip());
	_gun->Render();

	for (auto bullet : _bullets)
		bullet->Render();
}

void Machinegun::Fire(Vector2 dir)
{
	if (_selected == false)
		return;

	if (_hp <= 0)
		return;

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

	SOUND->Play("Cup_Attack", 0.3f);

	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
		[](const shared_ptr<Cup_Bullet>& obj)-> bool {return !obj->_isActive; });

	if (bulletIter == _bullets.end())
		return;

	//Vector2 dir = W_MOUSE_POS - _collider->GetTransform()->GetWorldPosition();

	(*bulletIter)->Shoot(Vector2(dir.x, dir.y), _gunTrans->GetWorldPosition());

	_hp -= 3;

	if (_hp <= 0)
		_hp = 0;

	_atkCool = true;

}
