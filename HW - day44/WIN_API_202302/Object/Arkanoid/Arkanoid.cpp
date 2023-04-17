#include "framework.h"
#include "Arkanoid.h"

Arkanoid::Arkanoid()
{
	_bar = make_shared<Bar>(Vector2(WIN_WIDTH * 0.5f, WIN_HEIGHT - 200.0f), Vector2(63, 37));

	_bricks.reserve(_poolCountY);
	Vector2 offset = { 400, 150 }; // offset 기준점에서 떨어져있다.
	for (int y = 0; y < _poolCountY; y++)
	{
		vector<shared_ptr<Brick>> bricksX;
		bricksX.reserve(_poolCountX);
		for (int x = 0; x < _poolCountX; x++)
		{
			shared_ptr<Brick> brick = make_shared<Brick>();
			Vector2 distance = { 60 * x, 34 * y };
			brick->SetPosition(offset + distance);
			bricksX.push_back(brick);
		}
		_bricks.push_back(bricksX);
	}
}

Arkanoid::~Arkanoid()
{
}

void Arkanoid::Update()
{
	_bar->Update();

	for (auto bricksX : _bricks)
	{
		for (auto brick : bricksX)
		{
			brick->Update();
		}
	}
}

void Arkanoid::Render(HDC hdc)
{
	_bar->Render(hdc);

	for (auto bricksX : _bricks)
	{
		for (auto brick : bricksX)
		{
			brick->Render(hdc);
		}
	}
}
