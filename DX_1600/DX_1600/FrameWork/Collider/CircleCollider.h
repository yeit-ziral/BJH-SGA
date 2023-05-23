#pragma once
class CircleCollider
{
public:
	CircleCollider(float radius);
	~CircleCollider();

	void Update();
	void Render();

	void CreateData();
	void CreateVertices();

	void SetPosition(Vector2 pos) { _transform->SetPosition(pos); }

private:
	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;

	Vector2 _center;
	float _radius;

};
