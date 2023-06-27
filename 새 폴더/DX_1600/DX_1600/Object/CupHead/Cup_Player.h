#pragma once
class Cup_Ani;
class Cup_Bullet;

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
	void Fire();
	void Jump();

	void Damaged(int damgae);
	const int& GetHp() const { return _hp; }
	void SetHP(int value) { _hp = value; }
	const int& GetMaxHp() { return _maxHp; }

	bool IsCollision_Bullets(shared_ptr<Collider> col);

	void SetGrounded();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }
	shared_ptr<Collider> GetCollider() { return _collider; }

	//void SetActive(bool value) { _isActive = value; }

	bool _isAlive = true;

	shared_ptr<Transform> GetTransform() { return _collider->GetTransform(); }

private:
	int _hp = 10;
	int _maxHp = 10;

	shared_ptr<Cup_Ani> _animation;
	shared_ptr<Collider> _collider;

	vector<shared_ptr<Cup_Bullet>> _bullets;

	float _speed = 200.0f;
	float _time = 0.0f;
	float _atkSpeed = 0.5f;
	bool _atkCool = false;

	float _jumpPower = 0.0f;
};

