#pragma once
class Cup_Ani;
class Cup_Bullet;
class inventory;


class Cup_Player
{
private:
	Cup_Player();
	~Cup_Player();
public:
	enum Gun
	{
		NORMAL,
		MACHINE,
		CHARGE
	};
	enum Item
	{
		NONE,
		HELMET,
		KINGBULLET,
		SCOPE,
		SPEEDBOOTS
	};

	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Cup_Player();
	}
	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}
	static Cup_Player* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void Update();
	void Render();
	void PostRender();

	void Move(Vector2 movePos) { _footCollider->GetTransform()->AddVector2(movePos); }
	void Input();
	void Fire();
	void Jump();

	void SetPosition(Vector2 pos) { _footCollider->SetPosition(pos); }

	void NormalFire();
	void MachineFire();
	void ChargeFire();

	void Damaged(int damage);

	bool IsCollision_Bullets(shared_ptr<Collider> col);

	void SetGrounded();

	shared_ptr<Collider> GetCollider() { return _collider; }
	shared_ptr<Collider> GetFootCollider() { return _footCollider; }

	int GetHp() { return _hp; }
	void SetHp(int value) { _hp = value; }
	void AddHP(int value) { _hp += value; if (_hp > _maxHp) _hp = _maxHp; }
	int GetMaxHp() { return _maxHp; }
	void AddMaxHp(int value) { _maxHp += value; _hp += value; }

	void Attacked(int value) { _hp -= value; }
	//void Hit();
	//void SetHit(bool value) { _isHit = value; }

	bool _isAlive = true;

	bool IsAlive();

	shared_ptr<Transform>GetFootTransform() { return _footCollider->GetTransform(); }

	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }

	virtual const Vector2& GetPos() { return GetTransform()->GetWorldPosition(); }

	void SetGunAngle();

	Gun GetNowGun() { return _nowGun; }

	shared_ptr<Transform> GetGunSlot() { return _gunSlot; }

	float GetJumpPower() { return _jumpPower; }
	void SetJumpPower(float value) { _jumpPower = value; }

	int GetGunHp();
	int GetGunMaxHp();
	void FixGun(int value);

	int GetNowGunDamage();

	void FillItem(Item value);

	int RandomNum(int min, int max) { return rand() % (max - min) + min; }

private:
	static Cup_Player* _instance;

	int _hp = 10;
	int _maxHp = 10;

	Gun _nowGun = Gun::NORMAL;

	shared_ptr<Cup_Ani> _animation;
	shared_ptr<Collider> _collider;

	shared_ptr<Collider> _footCollider;

	// ÃÑ class ¹Þ±â
	//shared_ptr<class Gun> _gun;
	shared_ptr<class NormalGun> _normalGun;
	shared_ptr<class Machinegun> _machineGun;
	shared_ptr<class ChargeGun> _chargeGun;


	float _speed = 1000.0f;
	float _time = 0.0f;

	float _jumpPower = 0.0f;

	shared_ptr<Transform> _gunSlot;

	Vector2 _gunDir;
	Vector2 _gunShootDir;

	shared_ptr<class HPBar> _hpBar;

	int _damage = 0;

	shared_ptr<class inventory> _inventory;
};