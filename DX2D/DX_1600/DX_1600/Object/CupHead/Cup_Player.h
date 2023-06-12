#pragma once
class Cup_Player
{
public:
	enum State
	{
		IDLE,
		JUMP,
		RUN,
		ATTACK
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void Input();
	void Jump();
	void Move(Vector2 movePos) { _col->GetTransform()->AddVector2(movePos); }
	void Attack();

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

	void SetAction(State state);
	void SetGrounded() { _isJump = false; }

	shared_ptr<Collider> GetCollider() { return _col; }

	virtual const Vector2& GetPos() { return _transform->GetPos(); }

	bool IsCollision_Bullets(shared_ptr<Collider> col);


	const vector<shared_ptr<class Cup_Bullet>>& GetBullet() { return _bullets; }

private:
	void SetLeft();
	void SetRight();

	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;
	shared_ptr<Transform> _transform;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	float _speed = 1000.0f;
	float _jumpPower = 0.0f;

	Vector2 _fixedPos;

	bool _isJump = false;
	bool _isAttack = false;
	bool _isRight = false;

	vector<shared_ptr<class Cup_Bullet>> _bullets;
};

