#include "framework.h"
#include "Bullets.h"

Bullets::Bullets(wstring file, Vector2 scale)
{
	_bullet = make_shared<Quad>(L"Resource/Bullet.png");
	_bullet->GetTransform()->SetScale(Vector2(0.05f, 0.05f));
}

Bullets::~Bullets()
{
}

void Bullets::Update()
{
	if (_isActive == false)
		return;
	_bullet->GetTransform()->AddVector2(_direction * _speed);

	// 화면의 가장자리에 부딫혔을 때
	if (_bullet->GetTransform()->GetPos().y < 0.0f || _bullet->GetTransform()->GetPos().y > WIN_HEIGHT)
		_isActive = false;
	if (_bullet->GetTransform()->GetPos().x < 0.0f || _bullet->GetTransform()->GetPos().x > WIN_WIDTH)
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
	_direction = dir.NormalVector2();
	float angle = _direction.Angle();
	_bullet->GetTransform()->SetAngle(angle);
}
