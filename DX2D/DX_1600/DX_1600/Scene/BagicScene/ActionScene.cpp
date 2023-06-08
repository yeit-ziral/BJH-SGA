#include "framework.h"
#include "ActionScene.h"

#include "../../Object/Zelda/Link.h"
#include "../../Object/Zelda/Item.h"

ActionScene::ActionScene()
{
	_link = make_shared<Link>();
	srand((unsigned int)time(nullptr));

	for (int i = 0; i < 5; i++)
	{
		int w = rand() % WIN_WIDTH + 1;
		int h = rand() % WIN_HEIGHT + 1;

		shared_ptr<Item> item = make_shared<Item>(Vector2(w, h));
		_potions.push_back(item);
	}
}

ActionScene::~ActionScene()
{
}

void ActionScene::Update()
{
	_link->Update();
	for (auto& item : _potions)
	{
		item->Update();
	}
	GetItem();
}

void ActionScene::Collider_Update()
{
	_link->Collider_Update();
	for (auto& item : _potions)
	{
		item->Collider_Update();
	}
}

void ActionScene::Render()
{
	_link->Render();
	for (auto& item : _potions)
	{
		item->Render();
	}
}

void ActionScene::PostRender()
{
	_link->PostRender();
	ImGui::Text("MonsterHP : % d", (int)_link->GetHp());
	ImGui::Text("MonsterHP : % d", (int)_link->GetAtk());
}

void ActionScene::GetItem()
{
	for (auto& item : _potions)
	{
		if (!item->GetActive())
			return;

		if (_link->GetCollider()->IsCollision(item->GetCollider()))
		{
			item->SetActive(false);
			_link->SetHp(10);
		}
	}
}
