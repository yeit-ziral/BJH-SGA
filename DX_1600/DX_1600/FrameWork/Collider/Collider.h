#pragma once
class CircleCollider;
class RectCollider;

class Collider
{
public:
	enum class ColliderType
	{
		NONE,
		CIRCLE,
		RECT
	};

	Collider();
	virtual~Collider();

	virtual void Update() abstract;
	virtual void Render() abstract;

	void CreateData();
	virtual void CreateVertices() abstract;

	bool IsCollision(shared_ptr<Collider> col);
	virtual bool IsCollision(Vector2 pos) abstract;
	virtual bool IsCollision(shared_ptr<CircleCollider> other) abstract;
	virtual bool IsCollision(shared_ptr<RectCollider> other) abstract;

	void SetRed() { _colorBuffer->SetColor(RED); _colorBuffer->Update(); }
	void SetGreen() { _colorBuffer->SetColor(GREEN); _colorBuffer->Update(); }

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }
	Vector2 GetPos() { return _transform->GetPos(); }

	const shared_ptr<Transform> GetTransform() { return _transform; }
	void SetParent(shared_ptr<Transform> transform) { _transform->SetParent(transform); }

	vector<Vertex> GetVertices() { return _vertices; }

protected:
	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<ColorBuffer> _colorBuffer;

	shared_ptr<Transform> _transform;

	ColliderType _type;
};

