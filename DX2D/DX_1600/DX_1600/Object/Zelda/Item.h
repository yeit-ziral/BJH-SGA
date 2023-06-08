#pragma once
class Item
{
public:
	Item(Vector2 curframe);
	~Item();

	void Collider_Update();
	void Update();
	void Render();

	int GetHp() { return _hp; }
	int SetHp(int value) { _hp += value; }

	void SetPos(Vector2 pos) { _collider->SetPosition(pos); }

	shared_ptr<CircleCollider> GetCollider() { return _collider; }

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _collider;

	int _hp;
};

