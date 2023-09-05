#pragma once
class Camera : public Singleton<Camera>
{
	friend class Singleton;
private:
	Camera();
	~Camera();

public:
	void Update();

	void PostRender();

	Transform* GetTransform() { return transform; }

private:
	void FreeMode();
	void TargetMode();

	void SetView();

private:
	Transform* transform;

	float moveSpeed = 20.0f;
	float rotSpeed = 5.0f;

	ViewBuffer* viewBuffer;
	Matrix		  viewMatrix;

	Vector3 oldPos;
};