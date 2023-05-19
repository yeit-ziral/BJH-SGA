#pragma once

class Player
{
public:
	Player(wstring file, Vector2 scale);
	~Player();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _player->GetTransform()->SetPosition(pos); }
	void SetParent(shared_ptr<Transform> parent) { _player->GetTransform()->SetParent(parent); _revolution->SetParent(parent); }

	shared_ptr<Transform> GetTransform() { return _player->GetTransform(); }
	shared_ptr<Transform> GetRevolution() { return _revolution; }

private:
	bool _isControlled = true;

	shared_ptr<Quad> _player;
	shared_ptr<Transform> _revolution;

	float _RAngle = 0.0f;
};