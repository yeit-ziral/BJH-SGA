#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new ViewBuffer();

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

	ImGui::Text("Camera Pos : %f, %f, %f", pos.x, pos.y, pos.z);// const char* => char*은 string을 넣으라는 소리이고, const는 "abcd" 이 형식으로 넣으라는 소리이다 string a가 아니라
	ImGui::Text("Camera Rot : %.3f, %.3f, %.3f", rot.x, rot.y, rot.z); // f앞에 .n 을 적어서 몇번째 자리까지 표현할지 정할 수 있음
	// 서식 지정자 %d(정수), %f(실수), %c(charactor), %s(string), %p(pointer) 등에 맞게 넣어줘야 함
}

Ray Camera::ScreenPointToRay(Vector3 screenPos) // screenPos : Near Plane에 찍히는 점의 위치
{
	Ray ray;
	ray.origin = transform->translation;

	///////////////////Direction

	Vector3 point;

	point.x = +(2.0f * screenPos.x) / WIN_WIDTH - 1.0f;
		//y를 뒤집어줘야 함-> viewport
	point.y = -(2.0f * screenPos.y) / WIN_HEIGHT + 1.0f;
	point.z = 1.0f; //FarZ

	//////////////Invporjection/////////////// 맨 아래 윈쪽을 0,0으로 유지하기 위해서

	Matrix projection = Environment::GetInstance()->GetProjMatrix();

	XMFLOAT4X4 proj;

	XMStoreFloat4x4(&proj, projection);

	point.x /= proj._11;
	point.y /= proj._22;

	////////////////invView/////////////

	Matrix invView = transform->GetWorld();

	ray.direction = point * invView;
	ray.direction.Normalize();

	return ray;
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

	//XMVECTOR   eyePos = transform->translation;
	//XMVECTOR focusPos = transform->translation + transform->Forward();
	//XMVECTOR upVector = transform->Up();

	//viewMatrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);

	viewMatrix = XMMatrixInverse(nullptr, transform->GetWorld());

	viewBuffer->SetData(viewMatrix, transform->GetWorld()); // transform->GetWorld()가 Inverse View이다
	viewBuffer->SetVSBuffer(1);
}
