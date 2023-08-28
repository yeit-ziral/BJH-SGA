#include "Framework.h"
#include "Quad.h"

Quad::Quad(Vector2 size)
{
	float L = -size.x * 0.5f;
	float R = +size.x * 0.5f;
	float B = -size.y * 0.5f;
	float T = +size.y * 0.5f;

	vertices =
	{
		{Vector3(L, T, 0.0f), Vector2(0,0)},
		{Vector3(R, T, 0.0f), Vector2(1,0)},
		{Vector3(L, B, 0.0f), Vector2(0,1)},
		{Vector3(R, B, 0.0f), Vector2(1,1)}
	};

	indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	mesh = new Mesh(vertices, indices);

	material = new Material();
	material->SetShader(L"Texture");

	worldBuffer = new MatrixBuffer();

	ScratchImage image;
	LoadFromWICFile(L"Texture/Landscape/Box.png", WIC_FLAGS_NONE, nullptr, image);

	CreateShaderResourceView
	(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);

	D3D11_SAMPLER_DESC samplerDesc = {};

	samplerDesc.Filter			 = D3D11_FILTER_MIN_MAG_MIP_POINT; //LOD 관련된 설정(가까운것은 세세하게 먼것은 대충 )
	samplerDesc.AddressU		 = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV		 = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW		 = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc	 = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD			 = 0;
	samplerDesc.MaxLOD			 = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);
	
}

Quad::Quad(vector<Vector3> points)
{
	vertices =
	{
		{Vector3(points[0].x, points[0].y, points[0].z), Vector2(0,0)},
		{Vector3(points[1].x, points[1].y, points[0].z), Vector2(1,0)},
		{Vector3(points[2].x, points[2].y, points[0].z), Vector2(0,1)},
		{Vector3(points[3].x, points[3].y, points[0].z), Vector2(1,1)}
	};

	indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	mesh = new Mesh(vertices, indices);

	material = new Material();
	material->SetShader(L"Texture");

	worldBuffer = new MatrixBuffer();

	ScratchImage image;
	LoadFromWICFile(L"Texture/Landscape/Box.png", WIC_FLAGS_NONE, nullptr, image);

	CreateShaderResourceView
	(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);

	D3D11_SAMPLER_DESC samplerDesc = {};

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; //LOD 관련된 설정(가까운것은 세세하게 먼것은 대충 )
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&samplerDesc, &samplerState);
}

Quad::~Quad()
{
	delete mesh;
	delete worldBuffer;

	srv->Release();
	samplerState->Release();
}

void Quad::Render()
{
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);

	material->SetMaterial();
	mesh->SetMesh();

	DC->PSSetShaderResources(0, 1, &srv);
	DC->PSSetSamplers(0, 1, &samplerState);

	DC->DrawIndexed(indices.size(), 0, 0);
}
