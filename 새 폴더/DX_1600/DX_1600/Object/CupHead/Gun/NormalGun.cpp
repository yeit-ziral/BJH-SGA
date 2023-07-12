#include "framework.h"
#include "NormalGun.h"
#include "../Cup_Bullet.h"

NormalGun::NormalGun()
{
	_gun = make_shared<Quad>(L"Resource/CupHead/weapon/Kar98.png");
	_gunTrans = make_shared<Transform>();
	_gunTrans->SetScale({ 5,5 });
}

NormalGun::~NormalGun()
{
}

void NormalGun::Update()
{
	_gunTrans->Update();

	if (KEY_PRESS(VK_LBUTTON))
	{
		SOUND->Play("Cup_Attack", 0.3f);

		// 마우스 방향으로 총알 쏘기
		Fire();

	}
}

void NormalGun::Render()
{
	_gunTrans->SetBuffer(0);
	_gun->Render();
}

void NormalGun::Fire()
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
