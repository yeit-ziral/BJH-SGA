#pragma once

struct Vector3
{
	//XMVECTOR vector;		// 각 변수에 직접 접근 불가능
	//XMFLOAT3 float3;		// 각 변수에 직접 접근 가능
	//
	//
	//XMMATRIX matrix;		// 각 변수에 직접 접근 불가능
	//XMFLOAT4X4 float4x4;	// 각 변수에 직접 접근 가능

	Vector3()
	{

	}

	Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{

	}

	Vector3(XMFLOAT3 value)
		:x(value.x), y(value.y), z(value.z)
	{

	}

	Vector3(XMVECTOR vector)
	{
		x = XMVectorGetX(vector);
		y = XMVectorGetY(vector);
		z = XMVectorGetZ(vector);
	}

	operator XMVECTOR() // 대입연산자 오버로딩 -> 대입연산이 가능하게 함
	{
		//XMVECTOR vector;

		//vector = XMVectorSet(x, y, z, 0.0f);

		//return vector;

		return XMVectorSet(x, y, z, 0.0f);
	}

	operator XMFLOAT3()
	{
		return XMFLOAT3(x, y, z);
	}


	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
};