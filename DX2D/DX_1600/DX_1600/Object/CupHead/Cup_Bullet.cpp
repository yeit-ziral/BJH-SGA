#include "framework.h"
#include "Cup_Bullet.h"

Cup_Bullet::Cup_Bullet()
{
	_bullet = make_shared<CircleCollider>(5.0f);
	_quad = make_shared<Quad>(L"Resource/Bullet.png");
	_transform = make_shared<Transform>();

	_transform->SetParent(_bullet->GetTransform());
	_transform->SetScale({ 0.05, 0.05f });
	_transform->SetPosition({ -10.0f, 0.0f });
}

Cup_Bullet::~Cup_Bullet()
{
}

void Cup_Bullet::Collider_Update()
{
	if (!_isActive)
		return;

	_bullet->Update();
}

void Cup_Bullet::Update()
{
	if (!_isActive)
		return;

	_bullet->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	if (_bullet->GetTransform()->GetWorldPosition().y > WIN_HEIGHT || _bullet->GetTransform()->GetWorldPosition().y < 0
		|| _bullet->GetTransform()->GetWorldPosition().x > WIN_WIDTH || _bullet->GetTransform()->GetWorldPosition().x < 0)
		_isActive = false;

	_transform->Update();
}

void Cup_Bullet::Render()
{
	if (!_isActive)
		return;

	_transform->SetBuffer(0);
	_quad->Render();
	_bullet->Render();
}

void Cup_Bullet::Shoot(Vector2 dir, Vector2 startPos)
{
	_isActive = true;

	_bullet->GetTransform()->SetPosition(startPos);

	_dir = dir.NormalVector2();
	float angle = _dir.Angle();
	_bullet->GetTransform()->SetAngle(angle);
}
