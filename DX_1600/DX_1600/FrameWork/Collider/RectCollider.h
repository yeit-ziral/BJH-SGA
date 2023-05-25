#pragma once

class RectCollider : public Collider
{
public:
	RectCollider(Vector2 size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	void CreateVertices();
	
	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	void SetScale(Vector2 scale) { _transform->SetScale(scale); }
	Vector2 GetWorldSize() const { return Vector2(_transform->GetWorldScale().x * _size.x, _transform->GetWorldScale().y * _size.y); }

	float Left() const { return _transform->GetWorldPosition().x - GetWorldSize().x * 0.5f; }
	float Right() const { return _transform->GetWorldPosition().x + GetWorldSize().x * 0.5f; }
	float Top() const { return _transform->GetWorldPosition().y - GetWorldSize().y * 0.5f; }
	float Bottom() const { return _transform->GetWorldPosition().y + GetWorldSize().y * 0.5f; }

private:
	Vector2 _size;
};