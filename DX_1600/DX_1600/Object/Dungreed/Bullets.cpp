#include "framework.h"
#include "Bullets.h"

Bullets::Bullets()
{
	_bullet = make_shared<Quad>(L"Resource/Bullet.png");
	_bullet->GetTransform()->SetScale(Vector2(0.1f, 0.1f));
}

Bullets::~Bullets()
{
}

void Bullets::Update()
{
	if (_isActive == false)
		return;

	_bullet->GetTransform()->AddVector2(_dir * _speed * DELTA_TIME);

	//// 화면의 가장자리에 부딫혔을 때
	if (_bullet->GetTransform()->GetWorldPosition().y > WIN_HEIGHT || _bullet->GetTransform()->GetWorldPosition().x > WIN_WIDTH
		|| _bullet->GetTransform()->GetWorldPosition().y < 0 || _bullet->GetTransform()->GetWorldPosition().x < 0)
		_isActive = false;

	_bullet->Update();
}

void Bullets::Render()
{
	if (_isActive == false)
		return;

	_bullet->Render();
}

void Bullets::Shoot(const Vector2& dir, Vector2 startPos)
{
	_isActive = true;

	_dir = dir.NormalVector2();
	float angle = _dir.Angle();
	_bullet->GetTransform()->SetPosition(startPos);
	_bullet->GetTransform()->SetAngle(angle);
}
