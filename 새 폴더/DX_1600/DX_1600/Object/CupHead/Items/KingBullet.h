#pragma once
class KingBullet
{
public:
	KingBullet();
	~KingBullet();

	void Update();
	void Render();

	bool _isActivated = false;

	shared_ptr<Collider> GetCollider() { return _collider; }

	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }

private:
	shared_ptr<Collider> _collider;
	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
};

