#pragma once
class Arkanoid
{
public:
	Arkanoid();
	~Arkanoid();

	void Update();
	void Render(HDC hdc);

	shared_ptr<Brick> GetBrick(int y, int x) { return _bricks[y][x]; }

private:
	vector<vector<shared_ptr<Brick>>> _bricks;

	shared_ptr<class Bar> _bar;

	UINT _poolCountX = 0;
	UINT _poolCountY = 0;
};