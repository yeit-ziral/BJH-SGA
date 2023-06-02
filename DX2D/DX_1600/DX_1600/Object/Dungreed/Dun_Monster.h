#pragma once
class Dun_Monster
{
public:
	Dun_Monster();
	~Dun_Monster();

	void Collider_Update();
	void Update();
	void Render();

	const int& GetHp() { return _hp; }

	void GetAttacked(int amount);

	bool _isAlive = true;

	shared_ptr<CircleCollider> GetCircleCollider() { return _monster; }

	void SetPosition(Vector2 pos) { _monster->SetPosition(pos); }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _monster;

	int _hp = 30;
};

