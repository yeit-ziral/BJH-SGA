#include "framework.h"
#include "FixingTool.h"

FixingTool::FixingTool()
{
	_collider = make_shared<RectCollider>(Vector2(30, 30));
	_quad = make_shared<Quad>(L"Resource/FixingTool.png");
	_transform = make_shared<Transform>();
	_transform->SetParent(_collider->GetTransform());
}

FixingTool::~FixingTool()
{
}

void FixingTool::Update()
{
	if (_isActivated != true)
		return;
	_collider->Update();
	_transform->Update();
}

void FixingTool::Render()
{
	if (_isActivated != true)
		return;
	_collider->Render();
	_transform->SetBuffer(0);
	_quad->Render();
}
