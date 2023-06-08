#include "framework.h"
#include "Item.h"

Item::Item(Vector2 curframe)
{
	Vector2 size = ADD_SRV(L"Resource/Iten_11x5.png")->GetImageSize();
	size.x /= 11;
	size.y /= 5;

	_sprite = make_shared<Sprite>(L"Resource/Iten_11x5.png", Vector2(11, 5), size);
	_sprite->SetCurFrame(curframe);

	_collider = make_shared<CircleCollider>((size.x + size.y) / 2);
	_transform = make_shared<Transform>();

	_transform->SetParent(_collider->GetTransform());
	_collider->SetPosition(CENTER + Vector2((int)rand, (int)rand));

	_hp = 10;
}

Item::~Item()
{
}

void Item::Update()
{
	if (_hp > 0)
	{
		_sprite->Update();
		_transform->Update();
	}
}

void Item::Render()
{
	if (_hp > 0)
	{
		_sprite->Update();
		_transform->Update();
	}
}

void Item::Collider_Update()
{
	if (_hp > 0)
	{
		_collider->Update();
	}
}