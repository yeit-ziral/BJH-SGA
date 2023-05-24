#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:

	// 상수 버퍼를 사용할 때 주의사항
	// 1. 16바이트 배수를 무조건 지켜야한다

	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity(); // 단위행렬
	};

	MatrixBuffer()
		:ConstantBuffer(&_data, sizeof(_data))
	{

	}

	virtual ~MatrixBuffer() {}

	void SetData(XMMATRIX value)
	{
		value = XMMatrixTranspose(value);
		_data.matrix = value;
	}

	Data _data;

private:
};

class ColorBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT4 color;
	};

	ColorBuffer()
		:ConstantBuffer(&_data, sizeof(Data))
	{

	}
	virtual ~ColorBuffer() {}

	void SetColor(XMFLOAT4 value) { _data.color = value; }

	Data _data;
};