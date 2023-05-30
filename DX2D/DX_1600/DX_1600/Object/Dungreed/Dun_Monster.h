#pragma once
class Dun_Monster
{
public:
	Dun_Monster();
	~Dun_Monster();

	void Update();
	void Render();

	int GetHp() { return _hp; }

	int GetAttacked() { return _hp -= 1; }

	bool _isAlive = true;

	shared_ptr<CircleCollider> GetCircleCollider() { return _monster; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _monster;

	int _hp;
};

