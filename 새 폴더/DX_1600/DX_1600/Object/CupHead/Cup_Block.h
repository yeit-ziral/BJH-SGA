#pragma once
class Cup_Block
{
public:
	Cup_Block(Vector2 pos);
	~Cup_Block();

	void Update();
	void Render();

	void SetPosition(Vector2 pos) { _collider->SetPosition(pos); }
	Vector2 GetPosition() { return _collider->GetTransform()->GetWorldPosition(); }

	bool _isActive = true;

private:
	shared_ptr<Collider> _colliderUp;
	shared_ptr<Collider> _colliderRight;
	shared_ptr<Collider> _colliderLeft;

	shared_ptr<Quad> _quad;
	shared_ptr<Transform> _transform;
};

