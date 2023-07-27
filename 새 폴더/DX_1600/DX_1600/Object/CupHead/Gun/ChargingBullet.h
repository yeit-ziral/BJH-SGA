#pragma once
class ChargingBullet
{
public:
	ChargingBullet();
	~ChargingBullet();

	void Update();
	void Render();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, bool isLoop);

	void Charging(Vector2 startPos);

	void Shoot(Vector2 dir, Vector2 startPos);

	void SetAngle(float value) { _bullet->GetTransform()->SetAngle(value); }

	bool _isActive = false;

	const shared_ptr<CircleCollider>& GetBulletCollider() { return _bullet; }

	bool IsCollision(shared_ptr<CircleCollider> other) { return _bullet->IsCollision(other); }

	Vector2 GetPosition() { return _transform->GetWorldPosition(); }

	void SetLeft();
	void SetRight();

	void SetScale(float radious) { _bullet->SetScale(radious); }
	float GetBulletRadious() { return _bullet->GetRadius(); }

private:
	bool _isEnd = false;

	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _bullet;

	shared_ptr<Action> _action;

	shared_ptr<Sprite> _sprite;

	Vector2 _dir = Vector2();
	float _speed = 450.0f;

	float _timer = 0.0f;
	const float _inactiveTime = 3.0f;

};

