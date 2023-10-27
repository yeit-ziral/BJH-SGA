#pragma once
class ColliderCapsule : public Collider
{
public:
	ColliderCapsule();
	~ColliderCapsule();


	virtual bool Collision(IN Ray& ray, OUT Contact* contact = nullptr) override;
	virtual bool Collision(class ColliderBox* other) override;
	virtual bool Collision(class ColliderSphere* other) override;
	virtual bool Collision(class ColliderCapsule* other) override;

private:
	virtual void CreateMesh() override;

private:

};