#pragma once

// GPS에 보내는 정보 : Vertex Buffer(정점의 정보), Constant Buffer(상수 버퍼-> 정점 움직이는 데 곱해줄 정보), Index Buffer()
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

