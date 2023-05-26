#pragma once
class RectCollider;

class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(float radius);
	virtual ~CircleCollider();

	virtual void Update() override;
	virtual void Render() override;

	virtual void CreateVertices() override;

	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	//Rect와 공유하지 않는 함수
	void SetScale(float value) { _transform->SetScale({ value, value }); }
	float GetRadius() { return _radius; }
	float GetWorldRadius() { return _radius * _transform->GetWorldScale().x; }

	// Matrix 상속 걸려있는 구조에서는 사용하지 않음
	bool Block(shared_ptr<CircleCollider> movable);


private:
	float _radius;
};