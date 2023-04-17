#pragma once
class Brick
{
public:
	

	Brick();
	~Brick();

	void Update();
	void Render(HDC hdc);

	void SetPosition(Vector2 pos) { _rect->SetCenter(pos); }

	const int& GetHp() { return _hp; }

	void Attacked() { _hp -= 10; }

	bool IsAlive() { return _hp <= 0; }

private:
	HBRUSH _brush;

	shared_ptr<Collider> _rect;

	int _hp;
};

