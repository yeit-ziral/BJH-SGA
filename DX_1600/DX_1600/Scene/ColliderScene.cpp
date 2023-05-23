#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rectCollider = make_shared<RectCollider>(Vector2(100.0f, 100.0f));

	_rectCollider->SetPosition(CENTER);

	_circleCollider = make_shared<CircleCollider>(150.0f);

	_circleCollider->SetPosition(CENTER);
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_rectCollider->Update();
	_circleCollider->Update();
}

void ColliderScene::Render()
{
	_rectCollider->Render();
	_circleCollider->Render();
}

void ColliderScene::PostRender()
{
}
