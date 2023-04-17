#pragma once
class RectCollider;
class Line;

class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(Vector2 center, float radius);
	virtual ~CircleCollider();

	virtual void Update()override;
	virtual void Render(HDC hdc)override;

	void SetCenter(const Vector2& value);
	const Vector2& GetCenter() { return _center; }

	void SetRadius(float radius);
	const float& GetRadius() { return _radius; }

	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<Line> other);

private:
	float _radius = 0;
};

