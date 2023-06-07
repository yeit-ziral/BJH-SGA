#include "framework.h"
#include "Item.h"

Item::Item(wstring path, Vector2 maxFrame, Vector2 size)
{
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
}

void Item::PostRender()
{
}
