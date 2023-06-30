#pragma once
class Cup_Ani
{
public:
	enum State
	{
		IDLE,
		JUMP,
		RUN,
		HIT,
		GHOST,
		END,
		NONE
	};

	Cup_Ani();
	~Cup_Ani();

	void Update();
	void Render();
	void PostRender();

	void CreateAction(wstring srvPath, string xmlPath, string actionName, Vector2 size, bool isLoop = true, float time = 0.1f);
	void StateControl();
	void SetParent(shared_ptr<Transform> parent) { _transform->SetParent(parent); }

	void SetState(State state);
	State GetState() { return _curState; }
	void SetStateIdle() { SetState(IDLE); }
	void DieEvent() { SetState(GHOST); }
	void EndEvent() { _isActive = false; }
	void DamagedEvent() { SetState(HIT); }

	void SetIsGround(bool value) { _isGround = value; }
	bool GetISGround() const { return _isGround; }
	bool GetIsRight() const { return _isRight; }

	bool IsActive() { return _isActive; }

private:
	bool _isActive = true;

	void SetLeft();
	void SetRight();

	vector<shared_ptr<Action>> _actions;
	vector<shared_ptr<Sprite>> _sprites;
	shared_ptr<Transform> _transform;

	State _curState = State::IDLE;
	State _oldState = State::IDLE;

	Vector2 _fixedPos;

	bool _isRight = true;

	bool _isGround = false;
};

