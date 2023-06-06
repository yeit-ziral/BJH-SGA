#pragma once
class Link
{
public:
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

private:
	bool _isEnd = false;

	shared_ptr<Sprite> _sprite;
	vector<shared_ptr<Action>> _actions;
	shared_ptr<Transform> _transform;

	shared_ptr<Action>* _curAction;
};

