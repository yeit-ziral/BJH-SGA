#pragma once
class RectCollider;

class CircleCollider : public Collider, public enable_shared_from_this<CircleCollider>
{
public:
	CircleCollider(float radius);
	virtual~CircleCollider() override;

	virtual void Update() override;
	virtual void Render() override;

	void CreateVertices();

	virtual bool IsCollision(Vector2 pos) override;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) override;
	virtual bool IsCollision(shared_ptr<RectCollider> other) override;

	//Rect와 공유하지 않는 함수
	void SetScale(float value) { _transform->SetScale({ value, value }); }
	float GetRadius() { return _radius; }
	float GetWorldRadius() { return _radius * _transform->GetWorldScale().x; }


private:
	float _radius;
};