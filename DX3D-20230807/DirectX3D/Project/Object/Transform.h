#pragma once

class Transform
{
public:
	Transform();
	virtual ~Transform();

	void Update();
	void UpdateWorld();

	Matrix& GetWorld() { return world; } // call by reference로 원본값 수정 가능하게 함

	void SetParent(Transform* parent) { this->parent = parent; }

public:
	Vector3 scale = { 1.0f, 1.0f, 1.0f };
	Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	Vector3 translation = { 0.0f, 0.0f, 0.0f };

protected:
	// SRT 따로 만들지 않음
	Matrix world;

	Vector3 pivot = {};

	Transform* parent = nullptr;
};