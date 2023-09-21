#include "framework.h"
#include "HPBar.h"


HPBar::HPBar(wstring path, Vector2 size)
{
	_transform = make_shared<Transform>();
	_quad = make_shared<Quad>(path, size);
	_quad->SetPS(ADD_PS(L"Shader/HpBarPS.hlsl"));

	_intBuffer = make_shared<IntBuffer>();

	_frameQuad		= make_shared<Quad>(L"Resource/UI/HpBarFrame", size + Vector2(_quad->GetImageSize().x * 6.2f, 0.0f));
	_frameTransform = make_shared<Transform>();
	//_frameTransform->SetParent(_transform);
	_frameTransform->SetPosition(Vector2(-_quad->GetImageSize().x * 6.2f, 0.0f) + _transform->GetWorldPosition());
}

HPBar::~HPBar()
{
}

void HPBar::Update()
{
	_transform->Update();
	_intBuffer->Update();
	_frameTransform->Update();
}

void HPBar::PostRender()
{
	_intBuffer->SetPSBuffer(0);
	_transform->SetBuffer(0);
	_quad->Render();
	_frameTransform->SetBuffer(1);
	_frameQuad->Render();
}
