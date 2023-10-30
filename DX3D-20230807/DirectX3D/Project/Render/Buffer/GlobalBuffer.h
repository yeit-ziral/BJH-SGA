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
		data.padding = 0.0f;
		data.ambientLight = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	struct Data
	{
		Vector3 direction;

		float padding;

		Vector4 ambientLight;
	} data;
};

class ViewBuffer : public ConstBuffer
{
public:
	ViewBuffer()
		: ConstBuffer(&data, sizeof(data)) // �θ��� ������ ȣ���ؼ� ������ ������ ���� ����
	{
		data.view = XMMatrixIdentity();
		data.inverseView = XMMatrixIdentity();
	}

	void SetData(Matrix view, Matrix inverseView)
	{
		data.view = XMMatrixTranspose(view);
		data.inverseView	= XMMatrixTranspose(inverseView);
	}

private:
	struct Data
	{
		Matrix view;
		Matrix inverseView;
	} data;
};

class MaterialBuffer : public ConstBuffer
{
public:
	MaterialBuffer()
		: ConstBuffer(&data, sizeof(Data))
	{

	}

	struct Data
	{
		Vector4 diffuse  = Vector4(1, 1, 1, 1);
		Vector4 specular = Vector4(1, 1, 1, 1);
		Vector4 ambient  = Vector4(1, 1, 1, 1);
		Vector4 emissive = Vector4(0, 0, 0, 0);

		int hasDiffuseMap  = 0;
		int hasSpecularMap = 0;
		int hasNormalMap   = 0;
		int hasAlphaMap	   = 0;

		float shininess = 24.0f;

		Vector3 padding = {};
	} data;
};

class RayBuffer : public ConstBuffer
{
public:
	RayBuffer()
		: ConstBuffer(&data, sizeof(data)) 
	{
		
	}

	struct Data
	{
		Vector3 origin		= {};
		float	outputSize	= 0;

		Vector3 direction	= {};
		float	padding		= 0;
	} data;
};

class BrushBuffer : public ConstBuffer
{
public:
	BrushBuffer()
		: ConstBuffer(&data, sizeof(data))
	{

	}

	struct Data
	{
		//int	type	= 1;
		int	type	= 0;
		Vector3 location = {};

		float	range = 10;
		Vector3 color = {0.0f, 0.5f, 0.0f};
	} data;
};

class FrameBuffer : public ConstBuffer
{
public:
	FrameBuffer()
		: ConstBuffer(&data, sizeof(data)) 
	{
		data.next.clip = -1; // ���� ������ ���ٰ� ����
	}

	struct Frame
	{
		int clip		= 0;
		UINT curFrame	= 0;
		float time		= 0.0f;
		float speed		= 1.0f;
	};

	struct Data
	{
		float takeTime		= 0.0f;
		float tweenTime		= 0.0f;
		float runningTime	= 0.0f;
		float padding		= 0.0f;

		Frame cur, next;
	} data;
};

class FloatValueBuffer : public ConstBuffer
{
public:
	FloatValueBuffer()
		: ConstBuffer(&data, sizeof(data))
	{

	}

	struct Data
	{
		float values[4] = {};
	} data;
};

class IntValueBuffer : public ConstBuffer
{
public:
	IntValueBuffer()
		: ConstBuffer(&data, sizeof(data))
	{

	}

	struct Data
	{
		int values[4] = {};
	} data;
};