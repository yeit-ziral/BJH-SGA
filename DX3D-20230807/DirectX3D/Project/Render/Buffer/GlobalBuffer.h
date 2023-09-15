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

class LightBuffer : public ConstBuffer
{
public:
	LightBuffer()
		: ConstBuffer(&data, sizeof(data)) // 부모의 생서자 호출해서 데이터 생성을 같이 해줌
	{
		data.direction = V_DOWN;
		data.padding = 0.0f;
		data.ambientLight = Vector4(0.1f, 0.1f, 0.1f, 0.1f);
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
		: ConstBuffer(&data, sizeof(data)) // 부모의 생서자 호출해서 데이터 생성을 같이 해줌
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
		Vector4 diffuse  = Vector4(1,1,1,1);
		Vector4 specular = Vector4(1,1,1,1);
		Vector4 ambient  = Vector4(1,1,1,1);

		int hasDiffuseMap  = 0;
		int hasSpecularMap = 0;
		int hasNormalMap   = 0;

		float shininess = 24.0f;
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