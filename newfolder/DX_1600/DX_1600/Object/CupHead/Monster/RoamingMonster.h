#pragma once
class RoamingMonster // 돌아다니다가 플레이어한테 돌진해서 자폭공격
{
public:

	RoamingMonster();
	~RoamingMonster();

	void Update(shared_ptr<Collider> collider);
	void Render();
	void PostRender();

	void Attack(shared_ptr<Collider> collider);

	void SetPosition(Vector2 pos) { _monster->GetTransform()->SetPosition(pos); }

	const int& GetHp() { return _hp; }
	void ResetHp() { _hp = _maxHp; }
	const int GetMaxHp() { return _maxHp; }

	void GetAttacked(int amount);

	bool _isAlive = true;
	shared_ptr<Collider> GetCollider() { return _monster; }

	shared_ptr<Transform> GetTransform() { return _monster->GetTransform(); }

	void Roaming();

	int GetDamage() { return _damage; }

	void Move(Vector2 movePos) { _monster->GetTransform()->AddVector2(movePos); }

	int RandomNum(int min, int max) { return rand() % (max - min) + min; }

private:
	void SetLeft();
	void SetRight();

	shared_ptr<CircleCollider> _monster;

	shared_ptr<Transform> _transform;

	shared_ptr<Quad> _monsterQuad;


	int _hp = 30;
	int _maxHp = 30;

	float _jumpPower = 0.0f;

	float _speed = 400.0f;
	float _time = 0.0f;
	float _atkTime = 0.0f;
	float _atkSpeed = 1.0f;


	int _damage = 3;

	bool _isRight = true;

	bool _seeEnemy = false;

	int movingDir = 0;
};

