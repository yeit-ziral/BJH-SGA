#include "framework.h"
#include "Gun.h"

#include "../Cup_Bullet.h"

Gun::Gun()
{
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
	for (auto& bullet : _bullets)
		bullet->Update();
}

void Gun::Render()
{
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
