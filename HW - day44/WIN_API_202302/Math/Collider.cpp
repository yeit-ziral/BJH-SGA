#include "framework.h"
#include "Collider.h"

bool Collider::_isDebugMode = false;
Collider::Collider(Vector2 center)
	: _center(center)
{
	_type = ColliderType::NONE;

	HPEN none = CreatePen(PS_SOLID, 0, BLACK);
	HPEN green = CreatePen(PS_SOLID, 1, GREEN);
	HPEN red = CreatePen(PS_SOLID, 1, RED);
	
	_pens.push_back(none);
	_pens.push_back(green);
	_pens.push_back(red);
}

Collider::~Collider()
{
	for (auto* pen : _pens)
	{
		DeleteObject(pen);
	}
}

void Collider::MoveCenter(const Vector2& value)
{
	_center += value;
}

void Collider::SetCenter(const Vector2& value)
{
	_center = value;
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
