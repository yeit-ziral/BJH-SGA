#pragma once
class Cup_Bullet;

class Cup_Monster
{
public:
	enum State
	{
		START,
		LOOP,
		END
	};

	Cup_Monster();
	~Cup_Monster();

	void Update(Vector2 targetPos);
	void Render();
	void PostRender();

	void Attack(Vector2 targetPos);

	void SetPosition(Vector2 pos) { _monster->SetPosition(pos); }
	
	void CreateAction(wstring srvpath, string xmlpath, string actionName, Vector2 size, Action::Type type, CallBack event = nullptr);

	void StartEvent() { _state = State::START; }
	void DieEvent() { _state = State::END; }
	//void EndEvent() { _isAlive = false; }

	const int& GetHp() { return _hp; }
	void ResetHp() { _hp = _maxHp; }
	const int GetMaxHp() { return _maxHp; }

	void GetAttacked(int amount);

	bool _isAlive = true;
	shared_ptr<Collider> GetCollider() { return _monster; }

	bool IsCollsion_Bullets(shared_ptr<Collider> col);

	shared_ptr<Transform> GetTransform() { return _monster->GetTransform(); }

	void Roaming();

	void SetBowAngle(Vector2 targetPos);

	int GetDamage() { return _damage; }

private:
	void SetLeft();
	void SetRight();

	bool _isEnd = false;

	State _state = State::START;

	shared_ptr<IntBuffer> _intBuffer;

	shared_ptr<CircleCollider> _monster;

	shared_ptr<Transform> _transform;

	vector<shared_ptr<Action>> _actions;

	vector<shared_ptr<Sprite>> _sprites;

	int _hp = 30;
	int _maxHp = 30;

	vector<shared_ptr<Cup_Bullet>> _bullets;
	float _speed = 200.0f;
	float _time = 0.0f;
	float _atkSpeed = 1.0f;

	shared_ptr<Transform> _bowSlot;

	shared_ptr<Quad> _bow;
	shared_ptr<Transform> _bowTrans;

	int _damage = 1;
};

