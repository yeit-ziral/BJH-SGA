#include "framework.h"
#include "NormalGun.h"
#include "../Cup_Bullet.h"

NormalGun::NormalGun()
{
}

NormalGun::~NormalGun()
{
}

void NormalGun::Update()
{
}

void NormalGun::Render()
{
}

//void NormalGun::Fire()
//{
//	if (_atkCool)
//	{
//		_time += DELTA_TIME;
//		if (_time > _atkSpeed)
//		{
//			_time = 0.0f;
//			_atkCool = false;
//		}
//		return;
//	}
//
//	auto bulletIter = std::find_if(_bullets.begin(), _bullets.end(),
//		[](const shared_ptr<Cup_Bullet>& obj)-> bool {return !obj->_isActive; });
//
//	if (bulletIter == _bullets.end())
//		return;
//
//
//	(*bulletIter)->Shoot(Vector2(dir.x, dir.y), this->->GetWorldPosition());
//
//	_atkCool = true;
//
//}
