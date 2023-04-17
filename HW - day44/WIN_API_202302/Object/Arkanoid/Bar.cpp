#include "framework.h"
#include "Bar.h"

Bar::Bar(Vector2 pos, Vector2 size)
	: _isActive(true)
{
	_body = make_shared<RectCollider>(pos, size);
	_bullet = make_shared<Bullet>();

	_brush = CreateSolidBrush(BLUE);
}

Bar::~Bar()
{
	DeleteObject(_brush);
}

void Bar::Update()
{
	if (!_isActive)
		return;

	Move();
	Fire();

	_body->Update();
	_bullet->Update();
}

void Bar::Render(HDC hdc)
{
	if (!_isActive)
		return;

	SelectObject(hdc, _brush);

	_body->Render(hdc);
	_bullet->Render(hdc);
}

void Bar::Move()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		_body->MoveCenter(Vector2(-1.0f, 0.0f));
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		_body->MoveCenter(Vector2(1.0f, 0.0f));
	}
}

void Bar::Fire()
{
	if (!_bullet->IsActive())
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			_bullet->SetPos(Vector2(_body->GetCenter().x, _body->GetCenter().y - 2.5f));
			_bullet->Shoot(Vector2(0, 1), 10.0f);
		}
	}
}
