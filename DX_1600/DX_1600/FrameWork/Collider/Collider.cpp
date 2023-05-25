#include "framework.h"
#include "Collider.h"

Collider::Collider()
{
	_type = ColliderType::NONE;
}

Collider::~Collider()
{
}

void Collider::CreateData()
{
	_vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex), _vertices.size());

	_vs = make_shared<VertexShader>(L"Shader/ColliderVS.hlsl");
	_ps = make_shared<PixelShader>(L"Shader/ColliderPS.hlsl");

	_transform = make_shared<Transform>();

	_colorBuffer = make_shared<ColorBuffer>();
	SetGreen();
}

bool Collider::IsCollision(shared_ptr<Collider> col)
{
	switch (col->_type)
	{
	case Collider::ColliderType::NONE:
	{
		return false;
		break;
	}
	case Collider::ColliderType::CIRCLE:
	{
		shared_ptr<CircleCollider> circle = dynamic_pointer_cast<CircleCollider>(col);
		return IsCollision(circle);
		break;
	}
	case Collider::ColliderType::RECT:
	{
		shared_ptr<RectCollider> rect = dynamic_pointer_cast<RectCollider>(col);
		return IsCollision(rect);
		break;
	}
	default:
		break;
	}
	return false;
}
