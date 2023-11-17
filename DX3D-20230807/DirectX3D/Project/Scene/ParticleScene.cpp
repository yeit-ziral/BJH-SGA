#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
	collider = new ColliderSphere(50);

	//particle = new Sprite(L"Effect/greenCore_4x4.png", Vector2(30, 30), 4, 4, true);

	//particle = new Spark(L"Effect/Star.png", true);
	//particle = new Spark(L"Effect/Star.png", false); // => °ËÀº»öÀÌ¶û º° µÚ ¹ÙÅÁÀÌ ³ª¿È

	particle = new Rain(L"Effect/rain.png");
	particle->Play({});
}

ParticleScene::~ParticleScene()
{
	delete collider;
	delete particle;
}

void ParticleScene::Update()
{
	//if (KEY_DOWN(VK_LBUTTON))
	//{
	//	Ray ray = CAMERA->ScreenPointToRay(mousePos);

	//	Contact contact;

	//	if (collider->Collision(ray, &contact))
	//	{
	//		particle->Play(contact.hitPoint);
	//	}
	//}

	collider->Update();
	particle->Update();
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
	particle->Render();
	collider->Render();
}

void ParticleScene::PostRender()
{
	particle->Debug();
}