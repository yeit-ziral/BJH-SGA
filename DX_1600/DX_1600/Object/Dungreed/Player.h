#pragma once

class Player
{
public:
	Player(wstring file, Vector2 scale);
	~Player();

	void Move();
	void Angle();
	void Shoot();

	vector<shared_ptr<Bullets>>& GetBullets() { return _bullets; }

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _player->GetTransform()->SetPosition(pos); }
	void SetParent(shared_ptr<Transform> parent) { _quad->GetTransform()->SetParent(parent); _revolution->SetParent(parent); }

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }
	shared_ptr<Transform> GetRevolution() { return _revolution; }


private:
	bool _isControlled = true;
	bool _canShoot = true;
	float _speed = 5.0f;

	shared_ptr<Quad> _player;
	shared_ptr<Quad> _bow;
	vector<shared_ptr<Bullets>> _bullets;
};

