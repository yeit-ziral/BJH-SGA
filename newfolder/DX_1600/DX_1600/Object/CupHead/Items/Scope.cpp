#include "framework.h"
#include "Scope.h"

Scope::Scope()
{
	_collider = make_shared<RectCollider>(Vector2(30, 30));
	_quad = make_shared<Quad>(L"Resource/Scope.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
}

Scope::~Scope()
{
}

void Scope::Update()
{
	if (_isActivated != true)
		return;
	_collider->Update();
	_transform->Update();
}

void Scope::Render()
{
	if (_isActivated != true)
		return;
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}

bool Scope::IsCollision(Cup_Player* a)
{
	if (a->GetCollider()->IsCollision(_collider) && _isActivated)
	{
		a->FillItem(Cup_Player::Item::SCOPE);

		_isActivated = false;

		return true;
	}

	return false;
}
