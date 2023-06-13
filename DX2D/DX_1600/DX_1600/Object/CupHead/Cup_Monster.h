#pragma once
class Cup_Monster
{
public:
	enum State
	{
		START,
		LOOP,
		END
	};

	Cup_Monster();
	~Cup_Monster();

	void Update();
	void Render();
	void PostRender();

	void SetPosition(Vector2 pos) { _monster->SetPosition(pos); }
	
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

	State _state = State::START;

	shared_ptr<CircleCollider> _monster;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	int _hp = 30;
};

