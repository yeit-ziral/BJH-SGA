#include "framework.h"
#include "EffectScene.h"

EffectScene::EffectScene()
{
}

EffectScene::~EffectScene()
{
}

void EffectScene::Update()
{
	if (KEY_DOWN(VK_LBUTTON))
	{
		EFFECT_PLAY("Exp", W_MOUSE_POS);
	}
}

void EffectScene::Render()
{
}
