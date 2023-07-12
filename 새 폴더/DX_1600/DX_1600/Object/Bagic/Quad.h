#pragma once
class Quad
{
public:
	Quad();
	Quad(wstring srvFile);
	Quad(wstring srvFile, Vector2 size);
	virtual ~Quad();

	virtual void Render();

	void SetPS(shared_ptr<PixelShader> ps) { _ps = ps; }
	void SetVS(shared_ptr<VertexShader> vs) { _vs = vs; }

	void CreateVertices();

	Vector2 GetQuadHalfSize() { return _halfSize; }
	Vector2 GetImageSize() { return _srv.lock()->GetImageSize(); }

	void FlipVertically();

protected:
	// ����(pos, color, uv) 6��
	Vector2 _halfSize;

	// Mesh
	vector<Vertex_Texture> _vertices;
	vector<UINT> _indices;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	// Material
	weak_ptr<VertexShader> _vs;
	weak_ptr<PixelShader> _ps;
	weak_ptr<SRV> _srv;
};

