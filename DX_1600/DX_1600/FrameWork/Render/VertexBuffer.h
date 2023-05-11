#pragma once
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void CreateVertices();
	void CreateVertexBuffer();

	void Set(int slot = 0);

private:
	vector<Vertex> vertices;
	ComPtr<ID3D11Buffer> vertexBuffer; // �������� ��Ƴ��� ����



	UINT stride;
	UINT offset;
};

