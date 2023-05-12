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

private:
	vector<Vertex> _vertices;
	vector<UINT> _indices;

	// ����(pos, color, uv) 6��
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
	shared_ptr<SRV> _srv;
	shared_ptr<SamplerState> _ss;
};

