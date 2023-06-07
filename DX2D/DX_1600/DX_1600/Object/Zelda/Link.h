#pragma once
class Link
{
public:
	enum State
	{
		IDLE_F,
		IDLE_B,
		IDLE_R,
		IDLE_L,
		RUN_F,
		RUN_B,
		RUN_R,
		RUN_L,
		NONE
	};

	State _state = State::IDLE_F;


	Link();
	~Link();

	void Update();
	void Render();
	void PostRender();

	void CreateActionFront();
	void CreateActionBack();
	void CreateActionRight();
	void CreateActionLeft();

	void SelectDir();

	void EndEvent() { _isEnd = true; }

	int GetHp() { return _hp; }
	int SetHp(int value) { _hp += value; }

	int GetAtk() { return _atk; }
	int SetAtk(int value) { _atk += value; }

private:
	bool _isEnd = false;

	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Transform> _transform;

	shared_ptr<Action>* _curAction;

	int _hp;
	int _atk;
};

