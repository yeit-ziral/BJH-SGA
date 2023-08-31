#include "framework.h"
#include "SpeedBoots.h"

SpeedBoots::SpeedBoots()
{
	_collider = make_shared<RectCollider>(Vector2(30, 30));
	_quad = make_shared<Quad>(L"Resource/SpeedBoots.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
}

SpeedBoots::~SpeedBoots()
{
}

void SpeedBoots::Update()
{
	if (_isActivated != true)
		return;
	_collider->Update();
	_transform->Update();
}

void SpeedBoots::Render()
{
	if (_isActivated != true)
		return;
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}
