#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer()
		: ConstBuffer(&data, sizeof(data)) // 부모의 생서자 호출해서 데이터 생성을 같이 해줌
	{
		data.matrix = XMMatrixIdentity();
	}

	void SetData(XMMATRIX value)
	{
		data.matrix = XMMatrixTranspose(value);
	}

private:
	struct Data
	{
		XMMATRIX matrix;
	} data;
};
