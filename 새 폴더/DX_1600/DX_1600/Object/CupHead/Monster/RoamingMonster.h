#pragma once
class RoamingMonster
{
public:
	enum State
	{
		START,
		LOOP,
		END
	};

	RoamingMonster();
	~RoamingMonster();

	void Update(Vector2 targetPos);
	void Render();
	void PostRender();

	void Attack(Vector2 targetPos);

	void SetPosition(Vector2 pos) { _monster->GetTransform()->SetPosition(pos); }

	void StartEvent() { _state = State::START; }
	void DieEvent() { _state = State::END; }

	const int& GetHp() { return _hp; }
	void ResetHp() { _hp = _maxHp; }
	const int GetMaxHp() { return _maxHp; }

	void GetAttacked(int amount);

	bool _isAlive = true;
	shared_ptr<Collider> GetCollider() { return _monster; }

	bool IsCollsion_Bullets(shared_ptr<Collider> col);

	shared_ptr<Transform> GetTransform() { return _monster->GetTransform(); }

	void Roaming();

	void SetBowAngle(Vector2 targetPos);

	int GetDamage() { return _damage; }

private:
	void SetLeft();
	void SetRight();

	bool _isEnd = false;

	State _state = State::START;

	shared_ptr<CircleCollider> _monster;

	shared_ptr<Quad> _monsterQuad;

	shared_ptr<Transform> _transform;


	int _hp = 30;
	int _maxHp = 30;

	vector<shared_ptr<class Cup_Bullet>> _bullets;
	float _speed = 200.0f;
	float _time = 0.0f;
	float _atkSpeed = 1.0f;

	shared_ptr<Transform> _bowSlot;

	shared_ptr<Quad> _bow;
	shared_ptr<Transform> _bowTrans;

	int _damage = 1;

	bool _isRight = true;
};

