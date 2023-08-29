#pragma once
class Cup_Ani;
class Cup_Bullet;


class Cup_Player
{
public:
	enum Gun
	{
		NORMAL,
		MACHINE,
		CHARGE
	};

	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos); }
	void Input();
	void Fire();
	void Jump();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	void NormalFire();
	void MachineFire();
	void ChargeFire();

	void Damaged(int damage);

	bool IsCollision_Bullets(shared_ptr<Collider> col);

	void SetGrounded();

	shared_ptr<Collider> GetCollider() { return _collider; }

	int GetHp() { return _hp; }
	void SetHP(int value) { _hp = value; }
	int GetMaxHp() { return _maxHp; }

	void Attacked(int value) { _hp -= value; }
	//void Hit();
	//void SetHit(bool value) { _isHit = value; }

	bool _isAlive = true;

	bool IsAlive();

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

private:
	int _hp = 10;
	int _maxHp = 10;

	Gun _nowGun = Gun::NORMAL;

	shared_ptr<Cup_Ani> _animation;
	shared_ptr<Collider> _collider;

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

	shared_ptr<class HPBar> _hpBar;

	int _damage = 0;
};