#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rectCollider = make_shared<RectCollider>(Vector2(100.0f, 100.0f));
	_rectCollider2 = make_shared<RectCollider>(Vector2(100.0f, 100.0f));
	_circleCollider = make_shared<CircleCollider>(150.0f);
	_circleCollider2 = make_shared<CircleCollider>(100.0f);
	_circleCollider->SetParent(_rectCollider->GetTransform());

	_rectCollider->SetPosition(CENTER);
	_rectCollider->SetScale(Vector2(1.5f, 1.5f));
	_circleCollider->SetPosition(Vector2(100.0f, 0.0f));
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	if (_circleCollider2->IsCollision(_circleCollider) || _circleCollider2->IsCollision(_rectCollider))
	{
		_circleCollider2->SetRed();
	}
	else
		_circleCollider->SetGreen();

	if (_rectCollider2->IsCollision(_circleCollider) || _rectCollider2->IsCollision(_rectCollider))
		_rectCollider2->SetRed();
	else
		_rectCollider2->SetGreen();

	_rectCollider->Update();
	_rectCollider2->Update();
	_circleCollider->Update();
	_circleCollider2->Update();
}

void ColliderScene::Render()
{
	_rectCollider->Render();
	_rectCollider2->Render();
	_circleCollider->Render();
	_circleCollider2->Render();
}

void ColliderScene::PostRender()
{
	ImGui::SliderFloat2("CirclePos", (float*)&_circlePos, 0, 1280);
	ImGui::SliderFloat2("RectPos", (float*)&_rectPos, 0, 1280);
	_circleCollider->SetPosition(_circlePos);
	_rectCollider2->SetPosition(_rectPos);
}
