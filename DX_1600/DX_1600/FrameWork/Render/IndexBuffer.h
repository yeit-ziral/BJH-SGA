#pragma once
class IndexBuffer
{
public:
	IndexBuffer(void* data, UINT count, UINT _offset);
	~IndexBuffer();

	void CreateIndexBuffer();

	void Set();

private:
	ComPtr<ID3D11Buffer> _indexBuffer; // �������� ��Ƴ��� ����

	// vertices �迭�� ����Ű�� ������
	void* _data = nullptr;

	UINT _count = 0;
	UINT _offset = 0;
};

