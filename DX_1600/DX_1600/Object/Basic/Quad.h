#pragma once
class Quad
{
public:
	Quad();
	Quad(wstring srvFile);
	~Quad();

	void Update();
	void Render();

	void CreateVertices();

	shared_ptr<Transform> GetTransform() { return _transform; }

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

private:
	vector<Vertex> _vertices;
	vector<UINT> _indices;

	// Á¤Á¡(pos, color, uv) 6°³
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
	shared_ptr<SRV> _srv;

	weak_ptr<Transform> _parent;

	shared_ptr<Transform> _transform;

	Vector2 leftTopPoint;
};

