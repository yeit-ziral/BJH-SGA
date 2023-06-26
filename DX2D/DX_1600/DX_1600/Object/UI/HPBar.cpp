#include "framework.h"
#include "HPBar.h"

HPBar::HPBar(wstring path, Vector2 size)
{
	_transform = make_shared<Transform>();
	_quad = make_shared<Quad>(path, size);
	_quad->SetPS(ADD_PS(L"Shader/HpBarPS.hlsl"));

	_intBuffer = make_shared<IntBuffer>();
}

HPBar::~HPBar()
{
}

void HPBar::Update()
{
	_transform->Update();
	_intBuffer->Update();
}

void HPBar::PostRender()
{
	_intBuffer->SetPSBuffer(0);
	_transform->SetBuffer(0);
	_quad->Render();
}
