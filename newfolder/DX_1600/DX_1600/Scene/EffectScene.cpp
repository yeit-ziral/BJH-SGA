#include "framework.h"
#include "EffectScene.h"
#include "../Object/CupHead/Monster/RoamingMonster.h"

EffectScene::EffectScene()
{
	_RMonster = make_shared<RoamingMonster>();
	_RMonster->SetPosition(Vector2(0, 0));

	CAMERA->SetPosition(Vector2(0, 0));
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
	if (KEY_DOWN(VK_RBUTTON))
	{
		EFFECT_PLAY("Exp2", W_MOUSE_POS);
	}
	//_RMonster->Update(PLAYER->GetCollider());
}

void EffectScene::Render()
{
	_RMonster->Render();
}
