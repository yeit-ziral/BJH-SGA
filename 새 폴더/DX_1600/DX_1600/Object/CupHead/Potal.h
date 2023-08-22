#pragma once
class Potal
{
public:
	Potal();
	~Potal();

	void Update();
	void Render();

	void CreateAction(wstring srvPath, string xmmlPath, string actionName, Vector2 size, bool isLoop);

	bool IsCollision(shared_ptr<CircleCollider> other) { return _collider->IsCollision(other); }

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }

	bool _isActive = false;

private:
	shared_ptr<Transform> _transform;

	shared_ptr<CircleCollider> _collider;

	shared_ptr<Action> _action;

	shared_ptr<Sprite> _sprite;
};