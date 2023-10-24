#pragma once

struct Ray
{
	Vector3 origin;
	Vector3 direction;
};

class Camera : public Singleton<Camera>
{
	friend class Singleton;
private:
	Camera();
	~Camera();

public:
	void Update();

	void Debug();

	Transform* GetTransform() { return transform; }

	Ray ScreenPointToRay(Vector3 screenPos);

	void SetTarget(Transform* target) { this->target = target; }

private:
	void FreeMode();
	void TargetMode();

	void SetView();

	void Save();
	void Load();

private:
	Transform* transform;

	float moveSpeed = 20.0f;
	float rotSpeed = 5.0f;

	ViewBuffer* viewBuffer;
	Matrix		  viewMatrix;

	Vector3 oldPos;

	Transform* target;

	float distance = 60.0f;
	float height = 60.0f;

	Vector3 destination;
	Vector3 focusOffset;

	float rotY = 0.0f;
	float destRot = 0.0f;

	float moveDamping = 5.0f;
	float rotDamping = 1.0f;
};