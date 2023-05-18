#include "framework.h"
#include "Bullets.h"

Bullets::Bullets(wstring file, Vector2 scale)
{
	_bullet = make_shared<Quad>(file);
	_bullet->GetTransform()->SetScale(scale);
}

Bullets::~Bullets()
{
}

void Bullets::Update()
{
	if (_isActive == false)
		return;
	_bullet->GetTransform()->MoveCenter(_direction * _speed);

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

void Bullets::Shoot(const Vector2& dir, float speed)
{
	_isActive = true;
	_direction = dir;
	_speed = speed;
}
