#include "framework.h"
#include "Dun_Ground.h"

Dun_Ground::Dun_Ground()
{
	float a = 0.5f * WIN_WIDTH;
	float b = 0.1f * WIN_HEIGHT;
	_ground = make_shared<RectCollider>(Vector2(WIN_WIDTH * 1.0f, 0.2f * WIN_HEIGHT));
	_ground->GetTransform()->SetPosition(Vector2(a, b));
}

Dun_Ground::~Dun_Ground()
{
}

void Dun_Ground::Update()
{
	_ground->Update();
}

void Dun_Ground::Render()
{
	_ground->Render();
}
