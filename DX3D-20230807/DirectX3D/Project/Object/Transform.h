#pragma once

class WorldBuffer;

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

	Vector3 GetGlobalScale() { return globalScale; }
	Vector3 GetGlobalPosition() { return globalPosition; }

	void Debug();

	void SetLabel(string label) { this->label = label; }

	void SetWorld(int hasAnimation = 0);

	bool& IsActive() { return isActive; }

public:
	Vector3 scale = { 1.0f, 1.0f, 1.0f };
	Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	Vector3 translation = { 0.0f, 0.0f, 0.0f };

	void SetPivot(Vector3 value) { pivot = value; }

protected:
	// SRT ���� ������ ����
	Matrix world;

	Vector3 pivot = {};

	Transform* parent = nullptr;

	Vector3 globalScale;
	Vector3 globalRotation;
	Vector3 globalPosition;

	Vector3 right, up, forward; // �� ��ü�� ������� ����(�� ��, ��, ��, ��, �Ʒ�)

	string label = "Label";

	WorldBuffer* worldBuffer;

	bool isActive = true; // ������ ������ �� ������ Ű�°� ���������� �̰ɷ� �Ǽ��� ���� ���ͼ� true�� ������
};