#pragma once
class IndexBuffer
{
public:
	IndexBuffer(void* data, UINT count, UINT _offset);
	~IndexBuffer();

	void CreateIndexBuffer();

	void Set();

private:
	ComPtr<ID3D11Buffer> _indexBuffer; // 정점들을 담아놓는 버퍼

	// vertices 배열을 가리키는 포인터
	void* _data = nullptr;

	UINT _count = 0;
	UINT _offset = 0;
};

