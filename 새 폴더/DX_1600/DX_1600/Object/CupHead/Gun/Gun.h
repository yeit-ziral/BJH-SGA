#pragma once
class Gun
{
public:
	Gun();
	virtual ~Gun();

	virtual void Update();
	virtual void Render();

	shared_ptr<Transform> GetTransform() { return _gunTrans; }

	bool IsCollision_Bullets(shared_ptr<Collider> col); // ÃÑ¿¡ ³Ñ±æ °Í

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, bool isLoop);

	void SetRight();
	void SetLeft();

protected:
	shared_ptr<Transform> _gunTrans;

	shared_ptr<Collider> _collider;

	vector<shared_ptr<class Cup_Bullet>> _bullets;

	shared_ptr<Action> _action;

	shared_ptr<Sprite> _gun;

	float _time = 0.0f;
	float _atkSpeed = 0.01f;
	bool _atkCool = false;

	bool _selected = false;
	
};

