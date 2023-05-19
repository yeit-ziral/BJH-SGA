#include "framework.h"
#include "DungreedScene.h"

DungreedScene::DungreedScene()
{
	_player = make_shared<Player>(L"Resource/Player.png", Vector2(0.1f, 0.1f));
	_player->GetTransform()->SetPosition(Vector2(100, 100));

	_bow = make_shared<Quad>(L"Resource/Bow.png");
	_bow->GetTransform()->SetParent(_bowSlot->GetTransform());
	_bow->GetTransform()->SetPosition({ 50, 0 });
	_bow->GetTransform()->SetAngle(-PI * 0.75f)
}

DungreedScene::~DungreedScene()
{
}

void DungreedScene::Update()
{

	_player->Update();
	_bow->Update();
}

void DungreedScene::Render()
{
	_player->Render();
	_bow->Render();
}
