#include "framework.h"
#include "BossHpBar.h"
#include "HPBar.h"

BossHpBar::BossHpBar()
{
	_collider = make_shared<RectCollider>(Vector2(200, 150));

	_hpBar = make_shared<HPBar>();
	_hpBar->GetTransform()->SetParent(_collider->GetTransform());
	_hpBar->GetTransform()->SetPosition(Vector2(50, 0));

	_frameTransform = make_shared<Transform>();
	_frameTransform->SetParent(_collider->GetTransform());
	_frameTransform->SetScale(Vector2(0.5f, 0.5f));

	_frameQuad = make_shared<Quad>(L"Resource/UI/HpBarFrame.png");


	_hpBar->GetTransform()->SetScale(Vector2(1, 600));

	_hpBar->GetTransform()->SetScale(Vector2(_frameTransform->GetWorldScale().x / 1.1f, _frameTransform->GetWorldScale().y * 0.9f));
}

BossHpBar::~BossHpBar()
{
}

void BossHpBar::Update()
{
	_collider->Update();

	_hpBar->Update();

	_frameTransform->Update();

	_hpBar->SetMaxHp(_maxHp);
	_hpBar->SetCurHp(_curHp);
}

void BossHpBar::Render()
{
	_hpBar->PostRender();
	_frameTransform->SetBuffer(0);
	_frameQuad->Render();
}
