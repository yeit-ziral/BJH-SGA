#pragma once

class Player
{
public:
	Player();
	~Player();

	void Update();
	void Render();

	void SetBowAngle();
	const Vector2& GetPos() { return _player->GetTransform()->GetPos(); }

	void Fire();

private:
	shared_ptr<Quad> _player;

	shared_ptr<Transform> _bowSlot;

	shared_ptr<Quad> _bow;

	vector<shared_ptr<Bullets>> _bullets;
};