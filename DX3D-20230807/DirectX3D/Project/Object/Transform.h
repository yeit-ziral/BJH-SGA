#pragma once

class MatrixBuffer;

class Transform
{
public:
	Transform();
	virtual ~Transform();

	void Update();
	void UpdateWorld();

	Matrix& GetWorld() { return world; } // call by reference로 원본값 수정 가능하게 함

	void SetParent(Transform* parent) { this->parent = parent; }

	Vector3	 Forward() { return forward; }
	Vector3 Backward() { return forward * -1; }
	Vector3    Right() { return right; }
	Vector3		Left() { return right * -1; }
	Vector3		  Up() { return up; }
	Vector3		Down() { return up * -1; }

	void Debug();

	void SetLabel(string label) { this->label = label; }

	void SetWorld();

public:
	Vector3 scale = { 1.0f, 1.0f, 1.0f };
	Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	Vector3 translation = { 0.0f, 0.0f, 0.0f };

	void SetPivot(Vector3 value) { pivot = value; }

protected:
	// SRT 따로 만들지 않음
	Matrix world;

	Vector3 pivot = {};

	Transform* parent = nullptr;

	Vector3 globalScale;
	Vector3 globalRotation;
	Vector3 globalPosition;

	Vector3 right, up, forward; // 각 객체의 상대적인 방위(내 앞, 뒤, 옆, 위, 아래)

	string label = "";

	MatrixBuffer* worldBuffer;
};