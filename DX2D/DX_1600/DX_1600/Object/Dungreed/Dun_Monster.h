#pragma once
class Dun_Monster
{
public:
	Dun_Monster();
	~Dun_Monster();

	void Collider_Update();
	void Update();
	void Render();

	int GetHp() { return _hp; }

	int GetAttacked(int amount);

	bool _isAlive = true;

<<<<<<< Updated upstream
	shared_ptr<CircleCollider> GetCircleCollider() { return _monster; }

	void SetPosition(Vector2 pos) { _monster->SetPosition(pos); }
=======
	shared_ptr<CircleCollider> GetMonsterCollider() { return _monster; }
>>>>>>> Stashed changes

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _monster;

	int _hp = 30;
};

