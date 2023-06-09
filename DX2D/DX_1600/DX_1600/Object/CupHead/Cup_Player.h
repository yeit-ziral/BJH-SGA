#pragma once
class Cup_Player
{
public:
	enum State
	{
		IDLE,
		JUMP,
		RUN_R,
		NONE
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size);
	void CreateRunAction();
	void SelectState();

	void Move(Vector2 movePos) { _col->GetTransform()->AddVector2(movePos); }
	void Input();
	void Jump();
	void AnimationControl();

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

	void SetGrounded() { _jumpPower = 0.0f; }

	shared_ptr<Collider> GetCollider() { return _col; }

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
};

