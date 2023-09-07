#pragma once
class RoamingMonster // 돌아다니다가 플레이어한테 돌진해서 자폭공격
{
public:

	RoamingMonster();
	~RoamingMonster();

	void Update(Vector2 targetPos);
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

	bool IsCollsion_Bullets(shared_ptr<Collider> col);

	shared_ptr<Transform> GetTransform() { return _monster->GetTransform(); }

	void Roaming();

	void SetBowAngle(Vector2 targetPos);

	int GetDamage() { return _damage; }

	void Move(Vector2 movePos) { _monster->GetTransform()->AddVector2(movePos); }

private:
	void SetLeft();
	void SetRight();

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

