#pragma once
class Cup_Player
{
public:
	enum State
	{
		IDLE,
		RUN_R,
		JUMP,
		ATTACK,
		NONE
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size, Action::Type type);
	void CreateIdleAction();
	void CreateRunAction();
	void CreateJumpAction();
	void SelectState();

	void Move(Vector2 movePos) { _col->GetTransform()->AddVector2(movePos); }
	void Input();
	void Jump();
	void AnimationControl();

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

	void SetGrounded() { _jumpPower = 0.0f; }

	shared_ptr<Collider> GetCollider() { return _col; }

	bool SetIsJump(bool value) { return _isJump = value; }
	bool GetIsJump() { return _isJump; }

	virtual const Vector2& GetPos() { return _transform->GetPos(); }

	bool IsCollision_Bullets(shared_ptr<Collider> col);

	void Fire();

	const vector<shared_ptr<class Cup_Bullet>>& GetBullet() { return _bullets; }

private:
	void SetLeft();
	void SetRight();

	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;
	shared_ptr<Transform> _transform;

	State _state = State::IDLE;

	float _speed = 200.0f;

	Vector2 _fixedPos;

	float _jumpPower = 0.0f;

	bool _isJump = false;

	shared_ptr<Transform> _bowTrans;

	vector<shared_ptr<class Cup_Bullet>> _bullets;
};

