#include "framework.h"
#include "Sprite.h"

Sprite::Sprite(wstring path, Vector2 maxFrame, Vector2 size)
	: _maxFrame(maxFrame)
	, Quad(path, size)
{
	_vs = ADD_VS(L"Shader/SpriteVS.hlsl");
	_ps = ADD_PS(L"Shader/SpritePS.hlsl");

	_frameBuffer = make_shared<FrameBuffer>();
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
	_transform->Update();
}

void Sprite::Render()
{
	_frameBuffer->SetPSBuffer(0);
	Quad::Render();
}
