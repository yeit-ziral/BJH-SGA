#pragma once
class HowitzerBullet
{
public:
	HowitzerBullet();
	~HowitzerBullet();

	void Update();
	void Render();

	void Shoot(Vector2 dir, Vector2 startPos);
	void EndEvent();

	void SetAngle(float value) { _bullet->GetTransform()->SetAngle(value); }

	bool _isActive = false;

	const shared_ptr<CircleCollider>& GetBulletCollider() { return _bullet; }

	bool IsCollision(shared_ptr<CircleCollider> other) { return _bullet->IsCollision(other); }

	Vector2 GetPosition() { return _transform->GetWorldPosition(); }

	int RandomNum(int min, int max) { return rand() % (max - min) + min; }

private:
	bool _isEnd = false;

	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _bullet;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	Vector2 _dir = Vector2();
	float _speed = 450.0f;

	float _timer = 0.0f;
	const float _inactiveTime = 3.0f;
};

