#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
	: _radius(radius)
{
	CreateData();
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	_transform->Update();
}

void CircleCollider::Render()
{
	_vertexBuffer->Set(0);

	_transform->SetBuffer(0);

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	_vs->Set();
	_ps->Set();

	DC->Draw(_vertices.size(), 0);
}

void CircleCollider::CreateData()
{
	CreateVertices();

	_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());

	_vs = make_shared<VertexShader>(L"Shader/ColliderVS.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/ColliderPS.hlsl");

	_transform = make_shared<Transform>();
}

void CircleCollider::CreateVertices()
{
    Vertex temp;

	float A = PI * (2.0f / 37.0f);

	for (int i = 0; i < 38; i++)
	{
		temp.pos = XMFLOAT3(_radius * cos(i * A), _radius * sin(i * A), 0.0f);
		_vertices.push_back(temp);
	}
}
