#include "framework.h"
#include "Gun.h"

#include "../Cup_Bullet.h"

Gun::Gun()
{
	_collider = make_shared<CircleCollider>(30.0f);

	for (int i = 0; i < 30; i++)
	{
		shared_ptr<Cup_Bullet> bullet = make_shared<Cup_Bullet>();
		_bullets.push_back(bullet);
	}
}

Gun::~Gun()
{
}

void Gun::Update()
{
	if (_selected == false)
		return;

	for (auto& bullet : _bullets)
		bullet->Update();
}

void Gun::Render()
{
	if (_selected == false)
		return;

	_gunTrans->SetBuffer(0);

	for (auto& bullet : _bullets)
		bullet->Render();
}

bool Gun::IsCollision_Bullets(shared_ptr<Collider> col)
{
	for (auto bullet : _bullets)
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
