#pragma once

class Transform
{
public:
	Transform();
	virtual ~Transform();

	void Update();
	void UpdateWorld();

	Matrix& GetWorld() { return world; } // call by reference�� ������ ���� �����ϰ� ��

	void SetParent(Transform* parent) { this->parent = parent; }

	Vector3	 Forward() { return forward; }
	Vector3 Backward() { return forward * -1; }
	Vector3    Right() { return right; }
	Vector3		Left() { return right * -1; }
	Vector3		  Up() { return up; }
	Vector3		Down() { return up * -1; }

public:
	Vector3 scale = { 1.0f, 1.0f, 1.0f };
	Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	Vector3 translation = { 0.0f, 0.0f, 0.0f };

protected:
	// SRT ���� ������ ����
	Matrix world;

	Vector3 pivot = {};

	Transform* parent = nullptr;

	Vector3 globalScale;
	Vector3 globalRotation;
	Vector3 globalPosition;

	Vector3 right, up, forward; // �� ��ü�� ������� ����(�� ��, ��, ��, ��, �Ʒ�)
};