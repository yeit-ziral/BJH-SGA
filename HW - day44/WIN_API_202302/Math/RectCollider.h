#pragma once
class RectCollider : public Collider
{
public:
	RectCollider(Vector2 center, Vector2 size);
	virtual ~RectCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void MoveSquare(const Vector2& value);

	/*void Set4Point(const Vector2& point1, const Vector2& point2, const Vector2& point3, const Vector2& point4);
	const Vector2& GetLeftTop() { return _leftTop; }
	const Vector2& GetRightTop() { return _rightTop; }
	const Vector2& GetLeftBottom() { return _leftBottom; }
	const Vector2& GetRightBottom() { return _rightBottom; }*/

	void SetSize(const Vector2& size);
	const Vector2& GetSize() { return _size; }

	virtual bool IsCollision(Vector2 pos) override;
	// AABB : 지금 우리가 만든것
	// Obb충돌 : 
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	float Left() const		{ return _center.x - _halfSize.x; }
	float Right() const		{ return _center.x + _halfSize.x; }
	float Top() const		{ return _center.y - _halfSize.y; }
	float Bottom() const	{ return _center.y + _halfSize.y; }
	
	const Vector2& GetHalfSize() { return _halfSize; }

private:
	Vector2 _leftTop = { 0.0f,0.0f };
	Vector2 _rightTop = { 0.0f,0.0f };
	Vector2 _leftBottom = { 0.0f,0.0f };
	Vector2 _rightBottom = { 0.0f,0.0f };

	Vector2 _size;
	Vector2 _halfSize;
};

