#pragma once
class Cup_Boss
{
public:

	enum Boss_State
	{
		START,
		LOOP,
		READY1,
		READY2,
		READY3,
		DASHREADY,
		DASHSTART,
		DASHLOOP,
		DASHSTOP,
		HOWITZER1,
		HOWITZER2,
		SHOOT1,
		SHOOT2,
		DIE
	};

	enum Boss_Attack
	{
		DASH,
		HOWITZER,
		SHOOT
	};

	Cup_Boss();
	~Cup_Boss();

	void Update(Vector2 target);
	void Render();
	void PostRender();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	shared_ptr<RectCollider> GetCollider() { return _collider; }

	void Attack(Vector2 target);

	void Dash();

	void Howitzer(Vector2 target);

	void Shoot(Vector2 target);

	void EndEventDash();

	void EndEvent();

	void DieEvent();

	void EndEventCrash();

	void Damage(int value) { _hp -= value; }

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos * DELTA_TIME); }

	bool _isAlive = true;

	int RandomNum(int min, int max) { return rand() % (max - min) + min; }

	bool _isWallCrash = false;

	int GetHp() { return _hp; }
	void ResetHp() { _hp = _maxHp; }

	void GetAttacked(int amount);

	bool IsCollsion_Bullets(shared_ptr<Collider> col);
	bool IsCollsion_HBullets(shared_ptr<Collider> col);

	Boss_State GetBossState() { return _state; }

	bool IsDash() { if (_state == DASHLOOP) return true; }

	void SetState(Boss_State value) { _state = value; }

	int GetDamage() { return _damage; }
	int GetDamageH() { return _damageH; }
	int GetDashDamage() { return _dashDamage; }

	int GetMaxHp() { return _maxHp; }

private:
	void SetLeft();
	void SetRight();
	int _hp = 45;
	int _maxHp = 45;


	bool _isLeft = true;



	int _coolDown = 3;

	shared_ptr<IntBuffer> _intBuffer;

	Boss_State _state = Boss_State::START;

	Boss_Attack _attackState = Boss_Attack::DASH;

	shared_ptr<RectCollider>_collider;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Cup_Bullet>> _bullets;
	vector<shared_ptr<class HowitzerBullet>> _Hbullets;

	int shootCount = 0;

	float _jumpPower = 0.0f;

	float waitTime = 0.0f;

	float _coolingtimeH = 1.5f;
	float _coolingtime = 0.5f;

	bool _atkCool = false;

	float _timer = 0.0f;

	int _damage = 1;
	int _damageH = 3;
	int _dashDamage = 5;
};

