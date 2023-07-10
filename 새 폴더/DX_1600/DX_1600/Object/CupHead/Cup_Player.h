#pragma once
class Cup_Ani;
class Cup_Bullet;
class Normalgun;

class Cup_Player
{
public:
	Cup_Player();
	~Cup_Player();

	void Update();
	void Render();
	void PostRender();

	void Move(Vector2 movePos) { _collider->GetTransform()->AddVector2(movePos); }
	void Input();
	//void Fire(); // ÃÑ¿¡ ³Ñ±æ °Í
	void Jump();

	void Damaged(int damgae);
	const int& GetHp() const { return _hp; }
	void SetHP(int value) { _hp = value; }
	const int& GetMaxHp() { return _maxHp; }

	//bool IsCollision_Bullets(shared_ptr<Collider> col);

	void SetGrounded();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); } 
	shared_ptr<Collider> GetCollider() { return _collider; }

	//void SetActive(bool value) { _isActive = value; }

	bool _isAlive = true;

	bool IsAlive();

	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }

	virtual const Vector2& GetPos() { return GetTransform()->GetPos(); }

private:
	int _hp = 10;
	int _maxHp = 10;

	shared_ptr<Cup_Ani> _animation;
	shared_ptr<Collider> _collider;

	// ÃÑ class ¹Þ±â
	//shared_ptr<class Gun> _gun;

	 // ÃÑ¿¡ ³Ñ±æ °Í

	float _speed = 1000.0f;
	float _time = 0.0f;

	float _jumpPower = 0.0f;
};