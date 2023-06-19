#pragma once
class Cup_Player
{
public:
	enum State
	{
		IDLE,
		JUMP,
		RUN,
		ATTACK,
		HIT
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void Input();
	void Jump();
	void Move(Vector2 dir) { dir.Normallize(); _col->GetTransform()->AddVector2(dir * DELTA_TIME * _speed); }
	void Attack();

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

	void SetAction(State state);
	void SetGrounded() { _isJump = false; }

	shared_ptr<Collider> GetCollider() { return _col; }

	virtual const Vector2& GetPos() { return _transform->GetPos(); }

	bool IsCollision_Bullets(shared_ptr<Collider> col);

	//Vector2 GetBulletPos() { return _bullets[2]->GetPosition(); };

	bool _isAlive = true;

	int GetHp() { return _hp; }
	void Attacked(int value) { _hp -= value; }
	void Hit();
	void SetHit(bool value) { _isHit = value; }

	shared_ptr<Transform> GetTransform() { return _col->GetTransform(); }

private:
	void SetLeft();
	void SetRight();

	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Action>> _actions;

	shared_ptr<IntBuffer> _intBuffer;
	vector<shared_ptr<Sprite>> _sprites;
	shared_ptr<Transform> _transform;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	float _speed = 1000.0f;
	float _jumpPower = 0.0f;

	Vector2 _fixedPos;

	bool _isJump = false;
	bool _isAttack = false;

	vector<shared_ptr<class Cup_Bullet>> _bullets;

	Vector2 _bulletPos;

	shared_ptr<Effect> _effect;

	int _hp;

	bool _isHit = false;
};

