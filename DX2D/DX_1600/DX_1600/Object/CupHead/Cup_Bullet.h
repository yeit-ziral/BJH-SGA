#pragma once
class Cup_Bullet
{
public:
	enum State
	{
		INTRO,
		LOOP
	};

	Cup_Bullet();
	~Cup_Bullet();

	void Update();
	void Render();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, bool isLoop);

	void Shoot(Vector2 dir, Vector2 startPos);
	void EndEvent();

	void SetAngle(float value) { _bullet->GetTransform()->SetAngle(value); }

	bool _isActive = false;

	const shared_ptr<CircleCollider>& GetBulletCollider() { return _bullet; }

	bool IsCollision(shared_ptr<CircleCollider> other) { return _bullet->IsCollision(other); }

	Vector2 GetPosition() { return _transform->GetWorldPosition(); }

private:
	State _state = State::INTRO;

	bool _isEnd = false;

	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _bullet;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	Vector2 _dir = Vector2();
	float _speed = 450.0f;

	void SetLeft();
	void SetRight();

	float _timer = 0.0f;
	const float _inactiveTime = 3.0f;
};