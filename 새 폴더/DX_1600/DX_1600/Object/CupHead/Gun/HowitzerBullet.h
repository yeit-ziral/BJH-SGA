#pragma once
class HowitzerBullet
{
public:
	HowitzerBullet(Vector2 target, Vector2 startPos);
	~HowitzerBullet();

	void Update();
	void Render();

	void Shoot(Vector2 target, Vector2 startPos);

	void CalculateYspeed(Vector2 target, Vector2 startPos);

	void EndEvent();

	void SetAngle(float value) { _bullet->GetTransform()->SetAngle(value); }

	bool _isActive = false;

	const shared_ptr<CircleCollider>& GetBulletCollider() { return _bullet; }

	bool IsCollision(shared_ptr<CircleCollider> other) { return _bullet->IsCollision(other); }

	Vector2 GetPosition() { return _transform->GetWorldPosition(); }

	int RandomNum(int min, int max) { return rand() % (max - min) + min; } // 총알의 _speed에만 적용

	float CalculateTime(float up) { return up / 15.0f; }

	float GetUpPower() { return _upPower; }
	float GetFrontPower() { return _speed; }

private:
	bool _isEnd = false;

	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _bullet;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	Vector2 _dir = Vector2();
	float _speed = 0.0f;

	const float _inactiveTime = 3.0f;

	float _upPower = 0.0f;

	float _timer = 0.0f;

	float _coolingtime = 0.0f;

	bool _atkCool = false;
};

