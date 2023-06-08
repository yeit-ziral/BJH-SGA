#pragma once
class Item
{
public:
	Item(Vector2 pos);
	~Item();

	void Collider_Update();
	void Update();
	void Render();

	int GetActive() { return _isActive; }
	int SetActive(int value) { return _isActive = value; }

	shared_ptr<CircleCollider> GetCollider() { return _collider; }

private:
	shared_ptr<Sprite> _sprite;
	shared_ptr<Transform> _transform;
	shared_ptr<CircleCollider> _collider;

	bool _isActive;
};

