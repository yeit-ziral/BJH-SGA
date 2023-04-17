#include "framework.h"
#include "Brick.h"

Brick::Brick()
{
	_rect = make_shared<RectCollider>(Vector2(0, 0), Vector2(58, 32));

	_brush = CreateSolidBrush(WHITE);
}

Brick::~Brick()
{
}

void Brick::Update()
{
	_rect->Update();
}

void Brick::Render(HDC hdc)
{
	if (IsAlive())
		SelectObject(hdc, _brush);
	_rect->Render(hdc);
}
