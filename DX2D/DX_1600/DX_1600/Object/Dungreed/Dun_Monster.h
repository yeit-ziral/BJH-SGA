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
private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _monster;

	int _hp;
};

