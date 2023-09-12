#include "framework.h"
#include "Helmet.h"

Helmet::Helmet()
{
	_collider = make_shared<RectCollider>(Vector2(30, 30));
	_quad = make_shared<Quad>(L"Resource/Helmet.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
}

Helmet::~Helmet()
{
}

void Helmet::Update()
{
	if (_isActivated != true)
		return;
	_collider->Update();
	_transform->Update();
}

void Helmet::Render()
{
	if (_isActivated != true)
		return;
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}

bool Helmet::IsCollision(Cup_Player* a)
{
	if (a->GetCollider()->IsCollision(_collider) && _isActivated)
	{
		a->FillItem(Cup_Player::Item::HELMET);

		_isActivated = false;

		return true;
	}


	return false;
}
