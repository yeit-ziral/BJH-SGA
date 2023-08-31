#include "framework.h"
#include "HpPotion.h"

HpPotion::HpPotion()
{
	_collider = make_shared<RectCollider>(Vector2(30, 30));
	_quad = make_shared<Quad>(L"Resource/HpPotion.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
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
