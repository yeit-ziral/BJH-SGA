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

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _bullet;

	Vector2 _dir = Vector2();
	float _speed = 150.0f;
};

