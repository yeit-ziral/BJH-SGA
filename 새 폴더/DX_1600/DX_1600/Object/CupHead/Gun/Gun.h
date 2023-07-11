#pragma once
class Gun
{
public:
	Gun();
	virtual ~Gun();

	virtual void Update();
	virtual void Render();

	virtual void Fire()abstract;

	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }

	bool IsCollision_Bullets(shared_ptr<Collider> col); // ÃÑ¿¡ ³Ñ±æ °Í

protected:
	shared_ptr<Quad> _gun;
	shared_ptr<Transform> _gunTrans;

	shared_ptr<Collider> _collider;

	vector<shared_ptr<class Cup_Bullet>> _bullets;

	float _time = 0.0f;
	float _atkSpeed = 0.5f;
	bool _atkCool = false;

	bool _selected = false;
	
};

