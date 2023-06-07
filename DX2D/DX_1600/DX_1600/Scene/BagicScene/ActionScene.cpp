#include "framework.h"
#include "ActionScene.h"
#include "../../Object/Zelda/Link.h"

ActionScene::ActionScene()
{
	_link = make_shared<Link>();
}

ActionScene::~ActionScene()
{
}

void ActionScene::Update()
{
	_link->Update();
}

void ActionScene::Render()
{
	_link->Render();
}

void ActionScene::PostRender()
{
	_link->PostRender();
	ImGui::Text("MonsterHP : % d", (int)_link->GetHp());
	ImGui::Text("MonsterHP : % d", (int)_link->GetAtk());
}