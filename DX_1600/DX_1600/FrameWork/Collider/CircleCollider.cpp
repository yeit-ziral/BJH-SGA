#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius)
	: _radius(radius)
{
	_type = ColliderType::CIRCLE;
	CreateVertices();
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

	_transform->SetBuffer(0);		// vs·Î º¸³¿

	_colorBuffer->SetPSBuffer(0);	// ps·Î º¸³¿

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

	_vs->Set();
	_ps->Set();

	DC->Draw(_vertices.size(), 0);
}

void CircleCollider::CreateVertices()
{
    Vertex temp;

	float A = PI * (1.0f / 18.0f);

	for (int i = 0; i < 37; i++)
	{
		temp.pos = XMFLOAT3(_radius * cos(i * A), _radius * sin(i * A), 0.0f);
		_vertices.push_back(temp);
	}
}

bool CircleCollider::IsCollision(Vector2 pos)
{
	float distance = (_transform->GetWorldPosition() - pos).Length();

	return distance < GetWorldRadius();
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	Vector2 center1= _transform->GetWorldPosition();
	Vector2 center2= other->_transform->GetWorldPosition();

	float distance = (center1 - center2).Length();

	float radius1 = GetWorldRadius();
	float radius2 = other->GetWorldRadius();

	return distance < GetWorldRadius() + other->GetWorldRadius();
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other)
{
	return other->IsCollision(shared_from_this());
}