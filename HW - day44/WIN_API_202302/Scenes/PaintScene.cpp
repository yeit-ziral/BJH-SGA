#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
	_circle = make_shared<CircleCollider>(Vector2(300.0f, 300.0f), 50.0f);
	
	//_circleMouse = make_shared<CircleCollider>(Vector2(0.0f, 0.0f), 70.0f);

	_rectMouse = make_shared<RectCollider>(Vector2(0.0f, 0.0f), Vector2(70, 100));

	_rectangle = make_shared<RectCollider>(Vector2(500.0f, 300.0f), Vector2(100, 150));
	
}

PaintScene::~PaintScene()
{
}

void PaintScene::Update()
{
	//Vector2 lerpResult = LERP(_circleMouse->GetCenter(), mousePos, 0.1f);
	Vector2 lerpResult = LERP(_rectMouse->GetCenter(), mousePos, 0.3f);

	//_circleMouse->SetCenter(lerpResult);
	_rectMouse->SetCenter(lerpResult);

	/*if (_circle->IsCollision(_circleMouse))
	{
		_circle->SetRed();
		_circleMouse->SetRed();
	}
	else
	{
		_circle->SetGreen();
		_circle->SetGreen();
	}*/
	if (_rectangle->IsCollision(_rectMouse))
	{
		_rectangle->SetRed();
		_rectMouse->SetRed();
	}
	else
	{
		_rectangle->SetGreen();
		_rectMouse->SetGreen();
	}
	if (_circle->IsCollision(_rectMouse))
	{
		_circle->SetRed();
		_rectMouse->SetRed();
	}
	else
	{
		_circle->SetGreen();
		_rectMouse->SetGreen();
	}

	_circle->Update();
	_rectangle->Update();
}

void PaintScene::Render(HDC hdc)
{
	_circle->Render(hdc);
	//_circleMouse->Render(hdc);
	_rectMouse->Render(hdc);
	_rectangle->Render(hdc);
}
