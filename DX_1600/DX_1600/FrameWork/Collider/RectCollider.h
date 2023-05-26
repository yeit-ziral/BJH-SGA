#pragma once

class RectCollider : public Collider
{
private:
	struct AABBRectInfo
	{
		float left = 0.0f;
		float top = 0.0f;
		float right = 0.0f;
		float bottom = 0.0f;
	};

	struct OBBRectInfo
	{
		Vector2 worldPos;
		Vector2 direction[2]; // 가로 세로 벡터
		float length[2]; // 가로 세로 길이
	};

public:
	RectCollider(Vector2 size);
	virtual ~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	void CreateVertices();
	
	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	void SetScale(Vector2 scale) { _transform->SetScale(scale); }
	Vector2 GetWorldSize() const { return Vector2(_transform->GetWorldScale().x * _size.x, _transform->GetWorldScale().y * _size.y); }

	AABBRectInfo GetAABBInfo();

	OBBRectInfo GetOBBRectInfo();

	// Matrix 상속 걸려있는 구조에서는 사용하지 않음
	bool Block(shared_ptr<RectCollider> movable);
	bool Block(shared_ptr<CircleCollider> movable);

private:
	Vector2 _size;
};