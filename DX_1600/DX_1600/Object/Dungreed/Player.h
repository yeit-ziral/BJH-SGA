#pragma once

class Player
{
public:
	Player(wstring file, Vector2 scale);
	~Player();

	void Update();
	void Render();

	void SetBowAngle(float angle);
	const Vector2& GetPos() { return _player->GetTransform()->GetPos(); }

	void SetPosition(Vector2 pos) { _player->GetTransform()->SetPosition(pos); }

	shared_ptr<Transform> GetTransform() { return _player->GetTransform(); }
	shared_ptr<Transform> GetRevolution() { return _bowSlot; }

private:
	bool _isControlled = true;

	shared_ptr<Quad> _player;
	shared_ptr<Transform> _bowSlot;

	float _RAngle = 0.0f;
};