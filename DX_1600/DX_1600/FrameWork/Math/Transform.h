#pragma once
class Transform
{
public:
	Transform();
	~Transform();

	void Update();
	void SetBuffer(UINT slot);

	void SetScale(Vector2 scale) { _scale = scale; }
	void SetAngle(float angle) { _angle = angle; }
	void SetPosition(Vector2 pos) { _pos = pos; }

	void AddScale(Vector2 value) { _scale += value; }
	void AddAngle(float value) { _angle += value; }
	void AddVector2(Vector2 value) { _pos += value; }

	void MoveCenter(const Vector2& value);

	const Vector2& GetScale() { return _scale; }
	const float& GetAngle() { return _angle; }
	const Vector2& GetPos() { return _pos; }

	const XMMATRIX& GetMatrix() { return _srt; }

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

	Vector2 GetWorldPosition();
	Vector2 GetWorldScale();

private:
	shared_ptr<class MatrixBuffer> _matrixBuffer; // world 받는 놈(다른 것도 넣을 수 있어서 matrix라고 함)

	Vector2 _scale = { 1.0f, 1.0f };
	float _angle = 0.0f;
	Vector2 _pos = { 0.0f, 0.0f };

	XMMATRIX _scaleM = XMMatrixIdentity();
	XMMATRIX _rotateM = XMMatrixIdentity();
	XMMATRIX _translateM = XMMatrixIdentity();

	XMMATRIX _srt = XMMatrixIdentity();

	weak_ptr<Transform> _parent;
};

