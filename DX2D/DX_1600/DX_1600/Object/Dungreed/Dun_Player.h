#pragma once
class Dun_Player
{
public:
	Dun_Player();
	~Dun_Player();

	void Update();
	void Render();

	void SetBowAngle();

	void SetPosition(Vector2 pos) { _player->GetTransform()->SetPosition(pos); }
	void Move(Vector2 movePos) { _player->GetTransform()->AddVector2(movePos); }
	const Vector2& GetPos() { return _player->GetTransform()->GetPos(); }

	void Fire();

	shared_ptr<CircleCollider> GetCircleCollider() { return _player; }

	vector<shared_ptr<class Dun_Bullet>> GetBullet() { return _bullets; }

private:
	shared_ptr<Quad> _quad;
	shared_ptr<CircleCollider> _player;

	shared_ptr<Transform> _bowSlot;
	shared_ptr<Quad> _bow;

	vector<shared_ptr<class Dun_Bullet>> _bullets;
};

