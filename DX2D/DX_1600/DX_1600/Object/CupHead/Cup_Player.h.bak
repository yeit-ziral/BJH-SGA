#pragma once
class Cup_Player
{
public:
	enum State
	{
		IDLE_R,
		IDLE_L,
		RUN_R,
		RUN_L,
		NONE
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void CreateAction();

	void CreateActionRight();
	void CreateActionLeft();

	void SelectDir();

	void SetPosition(Vector2 pos) { _col->SetPosition(pos); }

private:
	shared_ptr<CircleCollider> _col;

	vector<shared_ptr<Action>> _actions;
	shared_ptr<Action>* _curAction;

	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _transform;

	Vector2 _fixedPos;
};

