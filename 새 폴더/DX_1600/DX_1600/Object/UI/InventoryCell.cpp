#include "framework.h"
#include "InventoryCell.h"

InventoryCell::InventoryCell()
{
	_collider = make_shared<RectCollider>(Vector2(50, 50));
	_quad = make_shared<Quad>(L"Resource/UI/InventoryCell.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform())
}

InventoryCell::~InventoryCell()
{
}

void InventoryCell::Update()
{
	_collider->Update();
	_transform->Update();
}

void InventoryCell::PostRender()
{
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}
