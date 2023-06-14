#pragma once
class Cup_Monster
{
public:
	enum State
	{
		START,
		LOOP,
		END,
		DEAD
	};

	Cup_Monster();
	~Cup_Monster();

	void Update();
	void Render();
	void PostRender();

	void Input();

	void SetPosition(Vector2 pos) { _monster->SetPosition(pos); }

	void SetAction(State state);
	
	void CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void EndEvent();

	const int& GetHp() { return _hp; }

	void GetAttacked(int amount);

	bool _isAlive = true;

	shared_ptr<CircleCollider> GetCircleCollider() { return _monster; }


private:
	void SetLeft();
	void SetRight();

	bool _isEnd = false;

	State _curState = State::START;
	State _oldState = State::START;

	shared_ptr<IntBuffer> _intBuffer;

	shared_ptr<CircleCollider> _monster;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	int _hp = 5;
};

