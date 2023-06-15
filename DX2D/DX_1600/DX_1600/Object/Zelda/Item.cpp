#include "framework.h"
#include "Item.h"

Item::Item(Vector2 pos)
{
	Vector2 size = ADD_SRV(L"Resource/Item_11x5.png")->GetImageSize();
	size.x /= 11;
	size.y /= 5;

	_sprite = make_shared<Sprite>(L"Resource/Item_11x5.png", Vector2(11, 5), size);

	_collider = make_shared<CircleCollider>((size.x + size.y) / 2);
	_transform = make_shared<Transform>();

	_transform->SetParent(_collider->GetTransform());
	_collider->SetPosition(pos);
}

Item::~Item()
{
}

void Item::Update()
{
	if (!_isActive)
		return;

	_sprite->Update();
	_transform->Update();
}

void Item::Render()
{
	if (!_isActive)
		return;
	_transform->SetBuffer(0);
	_sprite->SetCurClip(Vector2(4, 0));
	_sprite->Render();
	_collider->Render();

}

void Item::Collider_Update()
{
	if (!_isActive)
		return;

	_collider->Update();
}