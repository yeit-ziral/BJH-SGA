#pragma once
class Bow
{
public:
	Bow(wstring file, Vector2 scale);
	~Bow();

	void Shoot();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _bow->GetTransform()->SetPosition(pos); }
	void SetParent(shared_ptr<Transform> parent) { _bow->GetTransform()->SetParent(parent); _revolution->SetParent(parent); }

	shared_ptr<Transform> GetTransform() { return _bow->GetTransform(); }
	shared_ptr<Transform> GetRevolution() { return _revolution; }

private:
	bool _isControlled = true;
	bool _canShoot = true;
	float _speed = 5.0f;

	shared_ptr<Quad> _bow;
	shared_ptr<Transform> _revolution;
	vector<shared_ptr<Bullets>> _bullets;

	float _angle = 0.0f;
};