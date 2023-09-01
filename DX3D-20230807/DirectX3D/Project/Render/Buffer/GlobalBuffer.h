#pragma once

class MatrixBuffer : public ConstBuffer
{
public:
	MatrixBuffer()
		: ConstBuffer(&data, sizeof(data)) // �θ��� ������ ȣ���ؼ� ������ ������ ���� ����
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

class LightBuffer : public ConstBuffer
{
public:
	LightBuffer()
		: ConstBuffer(&data, sizeof(data)) // �θ��� ������ ȣ���ؼ� ������ ������ ���� ����
	{
		data.direction = V_DOWN;
	}

	void SetData(Vector3 direction)
	{
		data.direction = direction;
	}

private:
	struct Data
	{
		Vector3 direction;

		float padding;
	} data;
};