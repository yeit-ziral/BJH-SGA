#include "framework.h"
#include "HpPotion.h"

HpPotion::HpPotion()
{
	_collider = make_shared<RectCollider>(Vector2(50, 50));
	_quad = make_shared<Quad>(L"Resource/HpPotion.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
	_transform->SetScale(Vector2(0.1f, 0.1f));
}

HpPotion::~HpPotion()
{
}

void HpPotion::Update()
{
	if (_isActivated != true)
		return;
	_collider->Update();
	_transform->Update();
}

void HpPotion::Render()
{
	if (_isActivated != true)
		return;
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}