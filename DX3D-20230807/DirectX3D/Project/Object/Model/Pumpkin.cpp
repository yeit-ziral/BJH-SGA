#include "Framework.h"
#include "Pumpkin.h"

Pumpkin::Pumpkin()
	:Model("Pumpkin")
{
	scale *= 0.005f;

	collider = new ColliderSphere();

}

Pumpkin::~Pumpkin()
{
	delete collider;
}

void Pumpkin::Update()
{
	Model::Update();
	collider->Update();

	collider->translation = Model::GetGlobalPosition();
	collider->translation += {0.0f, 0.4f, 0.0f};

	collider->scale = scale * 130.0f;

	if (speed > 0.0f)
		speed -= (Time::Delta() * 0.1f);

	translation.y -= Time::Delta() * 0.5f;
	translation += direction * speed * Time::Delta();

	nowTime += Time::Delta();

	//Appear();

	if (KEY_DOWN(VK_LBUTTON))
		Throw();

	if (translation.z > 1000)
		isAppear = false;
}

void Pumpkin::Render()
{
	if (!isAppear)
		return;
	Model::Render();
	collider->Render();
}

void Pumpkin::Debug()
{
	Model::Debug();
}

void Pumpkin::Throw()
{
	if (nowTime > 5.0f)
	{
		nowTime = 0.0f;
		translation = CAMERA->GetGlobalPosition();
		isAppear = false;
	}
	else
	{
		Ray ray = CAMERA->ScreenPointToRay(mousePos);

		direction = ray.direction.GetNormalized();

		isAppear = true;
		speed = 700;
	}
}

//void Pumpkin::Appear()
//{
//	if (nowTime / time > 1)
//	{
//		nowTime = 0;
//
//		if (!isAppear)
//		{
//			isAppear = true;
//		}
//		else
//		{
//			isAppear = false;
//
//			translation = RandomPosition();
//		}
//	}
//	else
//	{
//		if (isAppear)
//			Move();
//	}
//}
//
//void Pumpkin::Move()
//{
//	if (nowTime < 1.5f)
//		translation.x += Time::Delta();
//	else
//		translation.x -= Time::Delta();
//}
//
//Vector3 Pumpkin::RandomPosition()
//{
//	Vector3 newPos;
//
//	newPos = CAMERA->GetGlobalPosition();
//
//	newPos.z = 0;
//
//	newPos.x += RandomNum(-2, 2);
//	newPos.y += RandomNum(-2, 2);
//	newPos.z += RandomNum(-2, 2);
//
//	return newPos;
//}
