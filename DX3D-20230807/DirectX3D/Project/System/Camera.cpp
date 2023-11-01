#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new ViewBuffer();

	transform = new Transform();

	//transform->translation = { 100, 120, -100 };
	//transform->rotation.x = 0.65f;
	//transform->rotation.y = 0.65f;

	Load();
}

Camera::~Camera()
{
	Save();

	delete transform;

	delete viewBuffer;
}

void Camera::Update()
{
	if (target == nullptr)
		FreeMode();
	else
		TargetMode(MODE2);
}

void Camera::Debug()
{
	ImGuiIO io = ImGui::GetIO();
	distance -= io.MouseWheel * moveSpeed;


	if (ImGui::TreeNode("Camera Option"))
	{
		Vector3 pos = transform->translation;
		Vector3 rot = transform->rotation;

		ImGui::Text("Camera Pos : %f, %f, %f", pos.x, pos.y, pos.z);// const char* => char*은 string을 넣으라는 소리이고, const는 "abcd" 이 형식으로 넣으라는 소리이다 string a가 아니라
		ImGui::Text("Camera Rot : %.3f, %.3f, %.3f", rot.x, rot.y, rot.z); // f앞에 .n 을 적어서 몇번째 자리까지 표현할지 정할 수 있음
		// 서식 지정자 %d(정수), %f(실수), %c(charactor), %s(string), %p(pointer) 등에 맞게 넣어줘야 함

		ImGui::SliderFloat("Height",   &height,   -10.0f, 100.0f);
		ImGui::SliderFloat("Distance", &distance, -10.0f, 100.0f);

		ImGui::SliderFloat("RotationY", &rotY, 0, XM_2PI);

		ImGui::SliderFloat("Camera MoveDamping", &moveDamping, 0.0f, 30.0f);
		ImGui::SliderFloat("Camera RotationDamping", &rotDamping, 0.0f, 30.0f);

		ImGui::TreePop();
	}
}

Ray Camera::ScreenPointToRay(Vector3 screenPos) // screenPos : Near Plane에 찍히는 점의 위치
{
	Ray ray;
	ray.origin = transform->translation;

	///////////////////Direction(Inverse ViewPort)

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

Vector3 Camera::WorldToScreenPoint(Vector3 worldPos)
{
	Vector3 screenPos;

	screenPos = XMVector3TransformCoord(worldPos, viewMatrix);
	screenPos = XMVector3TransformCoord(screenPos, Environment::GetInstance()->GetProjMatrix());

	screenPos = (screenPos + Vector3(1, 1, 1)) * 0.5f;

	screenPos.x *= WIN_WIDTH;
	screenPos.y *= WIN_HEIGHT;

	return screenPos;
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

		if (abs(dir.x) > 15.0f || abs(dir.y) > 15.0f)
			dir = Vector3(0.0f, 0.0f, 0.0f);

		transform->rotation.y += dir.x * rotSpeed * Time::Delta();
		transform->rotation.x += dir.y * rotSpeed * Time::Delta();

	}

	viewMatrix = XMMatrixInverse(nullptr, transform->GetWorld());

	oldPos = mousePos;

	SetView();
}

void Camera::TargetMode(Mode mode)
{

	if (KEY_PRESS(VK_UP))
		height += moveSpeed * Time::Delta();
	if (KEY_PRESS(VK_DOWN))
		height -= moveSpeed * Time::Delta();

	switch (mode)
	{
	case Camera::MODE1: 
	{
		if (KEY_PRESS(VK_RBUTTON))
		{
			Vector3 dir = mousePos - oldPos;

			rotY += dir.x * rotSpeed * Time::Delta();
		}
		oldPos = mousePos;

		destRotY = LERP(destRotY, rotY, rotDamping * Time::Delta());

		XMMATRIX rotMatrix = XMMatrixRotationY(destRotY + rotY);

		Vector3 forward = V_FORWARD * rotMatrix;

		destination = target->GetGlobalPosition() + forward * distance + V_UP * height;

		transform->translation = LERP(transform->translation, destination, moveDamping * Time::Delta());

		viewMatrix = XMMatrixLookAtLH(transform->translation, target->translation, V_UP);

	}
		break;
	case Camera::MODE2:
	{


		if (KEY_PRESS(VK_RBUTTON))
		{
			Vector3 dir = mousePos - oldPos;

			transform->rotation.y += dir.x * rotSpeed * Time::Delta();
			transform->rotation.x += dir.y * rotSpeed * Time::Delta();


			rotY += dir.x * rotSpeed * Time::Delta();
		}

		oldPos = mousePos;

		destRotX = LERP(destRotX, transform->rotation.x, rotDamping * Time::Delta());
		destRotY = LERP(destRotY, transform->rotation.y, rotDamping * Time::Delta());

		XMMATRIX rotMatrix = XMMatrixRotationRollPitchYaw(destRotX, destRotY + rotY, 0.0f);

		Vector3 forward = V_FORWARD * rotMatrix;

		destination = target->GetGlobalPosition() + forward * distance;

		transform->translation = LERP(transform->translation, destination, moveDamping * Time::Delta());

		viewMatrix = XMMatrixLookAtLH(transform->translation, target->translation, V_UP);

		viewMatrix *= XMMatrixTranslation(0, -height, 0);
	}
		break;
	default:
		break;
	}

	SetView();
}
//
//void Camera::TargetMode()
//{
//	//destination = target->translation - target->Backward() * distance + V_UP * height;
//
//	//transform->translation = destination;
//
//	//viewMatrix = XMMatrixLookAtLH(pos, target->translation, V_UP);
//
//	//destination = target->translation - V_FORWARD * distance + V_UP * height; // 기존 탑뷰
//
//	//transform->translation = destination;
//
//	//viewMatrix = XMMatrixLookAtLH(destination, target->translation, V_UP);
//
//	//destRot = LERP(destRot, target->rotation.y, rotDamping * Time::Delta()); // 살짝 숄더뷰 + 뎀핑
//
//	//XMMATRIX rotMatrix = XMMatrixRotationY(destRot + rotY);
//
//	//Vector3 forward = V_FORWARD * rotMatrix;
//
//	//destination = target->GetGlobalPosition() + forward * distance + V_UP * height;
//
//	//transform->translation = LERP(transform->translation, destination, moveDamping * Time::Delta());
//
//	//viewMatrix = XMMatrixLookAtLH(transform->translation, target->translation, V_UP);
//
//}

void Camera::SetView()
{
	transform->Update();

	//XMVECTOR   eyePos = transform->translation;
	//XMVECTOR focusPos = transform->translation + transform->Forward();
	//XMVECTOR upVector = transform->Up();

	//viewMatrix = XMMatrixLookAtLH(eyePos, focusPos, upVector);


	viewBuffer->SetData(viewMatrix, transform->GetWorld()); // transform->GetWorld()가 Inverse View이다
	viewBuffer->SetVSBuffer(1);
}

void Camera::Save()
{
	BinaryWriter data(L"CameraData");

	data.WriteData(transform->scale);
	data.WriteData(transform->rotation);
	data.WriteData(transform->translation);
}

void Camera::Load()
{
	BinaryReader data(L"CameraData");

	if (!data.Succeeded())
		return;

	transform->scale		= data.ReadVector3();
	transform->rotation		= data.ReadVector3();
	transform->translation	= data.ReadVector3();
}
