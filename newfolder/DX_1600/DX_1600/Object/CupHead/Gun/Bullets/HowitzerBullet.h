#pragma once
class HowitzerBullet
{
public:
	HowitzerBullet();
	~HowitzerBullet();

	void Update();
	void Render();
	void PostRender();

	void Shoot(Vector2 target, Vector2 startPos);

	void CalculateYspeed(Vector2 target, Vector2 startPos);

	void EndEvent();

	void SetAngle(float value) { _bullet->GetTransform()->SetAngle(value); }

	bool _isActive = false;

	const shared_ptr<CircleCollider>& GetBulletCollider() { return _bullet; }

	bool IsCollision(shared_ptr<CircleCollider> other) { return _bullet->IsCollision(other); }

	Vector2 GetPosition() { return _transform->GetWorldPosition(); }

	int RandomNum(int min, int max) { return rand() % (max - min) + min; } // �Ѿ��� _speed���� ����

	float CalculateTime(float up) { return up / 15.0f; }

	float GetUpPower() { return _upPower; }
	float GetFrontPower() { return _speed; }

	void NormalizeDir() { Vector2 dir = { _speed, _upPower }; _dir = dir.NormalVector2(); }

private:
	bool _isEnd = false;

	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _bullet;

	shared_ptr<Quad> _quad;

	Vector2 _dir = Vector2();
	float _speed = 0.0f;

	const float _inactiveTime = 3.0f;

	float _upPower = 0.0f;

	float _timer = 0.0f;

	float _speedFixingNum = 0.0f;

	float _activeTimer = 0.0f;

	float _extictTime = 5.0f;
};

