#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new MatrixBuffer();

	transform = new Transform();

	transform->translation = { 120, 100, -20 };
	transform->rotation.x = 0.65f;
}

Camera::~Camera()
{
	delete transform;

	delete viewBuffer;
}

void Camera::Update()
{
	FreeMode();
}

void Camera::PostRender()
{
	Vector3 pos = transform->translation;
	Vector3 rot = transform->rotation;

	ImGui::Text("Camera Pos : %d, %d, %d", pos.x, pos.y, pos.z);// const char* => char*�� string�� ������� �Ҹ��̰�, const�� "abcd" �� �������� ������� �Ҹ��̴� string a�� �ƴ϶�
	ImGui::Text("Camera Rot : %.3f, %.3f, %.3f", rot.x, rot.y, rot.z); // f�տ� .n �� ��� ���° �ڸ����� ǥ������ ���� �� ����
	// ���� ������ %d(����), %f(�Ǽ�), %c(charactor), %s(string), %p(pointer) � �°� �־���� ��
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS(VK_LSHIFT))
			moveSpeed = 50.0f;
		else
			moveSpeed = 20.0f;

		if (KEY_PRESS('A'))
			transform->translation += transform->Left()			* moveSpeed * Time::Delta();

		if (KEY_PRESS('D'))
			transform->translation += transform->Right()		* moveSpeed * Time::Delta();

		if (KEY_PRESS('S'))
			transform->translation += transform->Backward()		* moveSpeed * Time::Delta();

		if (KEY_PRESS('W'))
			transform->translation += transform->Forward()		* moveSpeed * Time::Delta();

		if (KEY_PRESS('Q'))
			transform->translation += transform->Up()			* moveSpeed * Time::Delta();

		if (KEY_PRESS('E'))
			transform->translation += transform->Down()			* moveSpeed * Time::Delta();

		Vector3 dir = mousePos - oldPos;

		transform->rotation.y += dir.x * rotSpeed * Time::Delta();
		transform->rotation.x += dir.y * rotSpeed * Time::Delta();





	}

	oldPos = mousePos;

	SetView();
}

void Camera::TargetMode()
{
}

void Camera::SetView()
{
	transform->Update();

	XMVECTOR   eyePos = transform->translation;
	XMVECTOR focusPos = transform->translation + transform->Forward();
	XMVECTOR upVector = transform->Up();

	viewMatrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	viewBuffer->SetData(viewMatrix);
	viewBuffer->SetVSBuffer(1);
}
