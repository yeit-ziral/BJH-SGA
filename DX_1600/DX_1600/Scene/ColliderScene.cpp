#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rectCollider = make_shared<RectCollider>(Vector2(100.0f, 100.0f));
	_rectCollider2 = make_shared<RectCollider>(Vector2(100.0f, 100.0f));
	_circleCollider = make_shared<CircleCollider>(50.0f);
	_circleCollider2 = make_shared<CircleCollider>(100.0f);
	_circleCollider2->SetParent(_rectCollider->GetTransform());

	_rectCollider->SetPosition(CENTER);
	_rectCollider->SetScale(Vector2(1.5f, 1.5f));
	_circleCollider2->SetPosition(Vector2(160.0f, 0.0f));
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_rectCollider->Update();
	_rectCollider2->Update();
	_circleCollider->Update();
	_circleCollider2->Update();

	if (_circleCollider->IsCollision(_circleCollider2) || _circleCollider->IsCollision(_rectCollider2))
	{
		_circleCollider->SetRed();
	}
	else
		_circleCollider->SetGreen();

	if (_rectCollider->IsCollision(_circleCollider2) || _rectCollider->IsCollision(_rectCollider2))
		_rectCollider->SetRed();
	else
		_rectCollider->SetGreen();

	_rectCollider2->SetPosition(MOUSE_POS);
	_rectCollider2->Block(_rectCollider);
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
	/*ImGui::SliderFloat2("CirclePos", (float*)&_circlePos, 0, 1280);
	ImGui::SliderFloat2("RectPos", (float*)&_rectPos, 0, 1280);
	_circleCollider2->SetPosition(_circlePos);
	_rectCollider2->SetPosition(_rectPos);*/
}
