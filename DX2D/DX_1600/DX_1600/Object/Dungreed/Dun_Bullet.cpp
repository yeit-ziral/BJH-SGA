#include "framework.h"
#include "Dun_Bullet.h"

Dun_Bullet::Dun_Bullet()
{
	_quad = make_shared<Quad>(L"Resource/Bullet.png");
	_quad->GetTransform()->SetScale({0.05, 0.05f});
	_bullet = make_shared<CircleCollider>(0.025f);
}

Dun_Bullet::~Dun_Bullet()
{
}

void Dun_Bullet::Update()
{
	if(!_isActive)
		return;

	_bullet->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	_quad->GetTransform()->SetPosition(_bullet->GetTransform()->GetWorldPosition());

	_bullet->Update();
	_quad->Update();
}

void Dun_Bullet::Render()
{
	if (!_isActive)
		return;

	_bullet->Render();
	_quad->Render();
}

void Dun_Bullet::Shoot(Vector2 dir, Vector2 startPos)
{
	_isActive = true;

	_bullet->GetTransform()->SetPosition(startPos);

	_dir = dir.NormalVector2();
	float angle = _dir.Angle();
	_quad->GetTransform()->SetAngle(angle);
}
