#pragma once
class Cup_Bullet
{
public:
	enum Bullet_State
	{
		INTRO,
		LOOP,
		NONE
	};

	Cup_Bullet();
	~Cup_Bullet();

	void Update();
	void Render();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size);

	void EndEvent() { _isEnd = true; }

	void Shoot(Vector2 dir, Vector2 startPos);

	bool _isActive = false;

	const shared_ptr<CircleCollider>& GetBulletCollider() { return _bullet; }

	bool IsCollision(shared_ptr<CircleCollider> other) { return _bullet->IsCollision(other); }

private:
	Bullet_State _state = Bullet_State::INTRO;

	bool _isEnd = false;

	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _bullet;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	Vector2 _dir = Vector2();
	float _speed = 150.0f;

	void SetLeft();
	void SetRight();
};

