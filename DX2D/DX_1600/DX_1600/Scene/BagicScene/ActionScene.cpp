#include "framework.h"
#include "ActionScene.h"
#include "../../Object/Zelda/Link.h"
#include "../../Object/Zelda/Item.h"

ActionScene::ActionScene()
{
	_link = make_shared<Link>();
	_potion = make_shared<Item>(Vector2(4, 0));

	_potion->SetPos(Vector2(100, 100));
}

ActionScene::~ActionScene()
{
}

void ActionScene::Update()
{
	_link->Update();
	_potion->Update();
}

void ActionScene::Collider_Update()
{
	_link->Collider_Update();
	_potion->Collider_Update();
}

void ActionScene::Render()
{
	_link->Render();
	_potion->Render();
}

void ActionScene::PostRender()
{
	_link->PostRender();
	ImGui::Text("MonsterHP : % d", (int)_link->GetHp());
	ImGui::Text("MonsterHP : % d", (int)_link->GetAtk());
}

void ActionScene::GetItem()
{
	if (_link->GetCollider()->IsCollision(_potion->GetCollider()))
	{
		_potion->SetHp(20);
	}
}
