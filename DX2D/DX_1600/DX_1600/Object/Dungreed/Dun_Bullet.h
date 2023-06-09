#pragma once
class Dun_Bullet
{
public:
	Dun_Bullet();
	~Dun_Bullet();

	void Collider_Update();
	void Update();
	void Render();

	void Shoot(Vector2 dir, Vector2 startPos);

	bool _isActive = false;

	const shared_ptr<CircleCollider>& GetBulletCollider() { return _bullet; }

	bool IsCollision(shared_ptr<CircleCollider> other) { return _bullet->IsCollision(other); }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _bullet;

	Vector2 _dir = Vector2();
	float _speed = 150.0f;
};

