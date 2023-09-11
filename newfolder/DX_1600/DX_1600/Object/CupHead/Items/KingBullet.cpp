#include "framework.h"
#include "KingBullet.h"

KingBullet::KingBullet()
{
	_collider = make_shared<RectCollider>(Vector2(30, 30));
	_quad = make_shared<Quad>(L"Resource/KingBullet.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
}

KingBullet::~KingBullet()
{
}

void KingBullet::Update()
{
	if (_isActivated != true)
		return;
	_collider->Update();
	_transform->Update();
}

void KingBullet::Render()
{
	if (_isActivated != true)
		return;
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}
