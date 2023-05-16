#pragma once

// GPS�� ������ ���� : Vertex Buffer(������ ����), Constant Buffer(��� ����-> ���� �����̴� �� ������ ����), Index Buffer()
class ConstantBuffer
{
public:
	ConstantBuffer(void* data, UINT dataSize);
	virtual ~ConstantBuffer();

	void Update();

	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);

private:
	ComPtr<ID3D11Buffer> _buffer;

	void* _data;
	UINT _dataSize;
};

