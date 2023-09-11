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

	int GetHp() { return _hp; }
	int GetMaxHp() { return _maxHp; }

	void FixHp(int value) 
	{
		_hp += value;
		if (_hp >= _maxHp)
			_hp = _maxHp;
	}

	bool _inIventory = false;

	int GetDamage() { return _damage; }

protected:
	shared_ptr<Transform> _gunTrans;

	shared_ptr<Collider> _collider;

	vector<shared_ptr<class Cup_Bullet>> _bullets;

	shared_ptr<Action> _action;

	shared_ptr<Sprite> _gun;

	float _time = 0.0f;
	float _atkSpeed = 0.0f;
	bool _atkCool = false;

	bool _selected = false;

	int _damage;

	int _hp = 100;
	int _maxHp = 100;
};

