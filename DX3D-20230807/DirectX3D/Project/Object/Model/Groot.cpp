#include "Framework.h"
#include "Groot.h"

Groot::Groot()
	:ModelAnimator("Groot")
{
	scale *= 0.35f;
	ReadClip("Sad Idle");
	ReadClip("Drunk Run Forward");
	ReadClip("Mutant Swiping");
	CreateTexture();

	reader->GetMaterial()[0]->Load(L"Groot.mat");

	weapon = new Model("Dwarven_Axe");
	weapon->GetReader()->GetMaterial()[0]->Load(L"Dwarven_Axe.mat");
	//weapon->scale *= 100.0f;

	leftHand = new Transform();

	weapon->SetParent(leftHand);

	weapon->rotation.x = XMConvertToRadians(-44);
	weapon->rotation.y = XMConvertToRadians(64);
	weapon->rotation.z = XMConvertToRadians(244);

	weapon->translation.x = -1;
	weapon->translation.y = 80;
	weapon->translation.z = -20;

	clips[ATTACK]->SetEndEvent(bind(&Groot::SetClip, this, IDLE), 0.7f); //bind(��ġ, �۵���ų ��ü, (�Ű������� ���� �־��༭ �Ű������� ���� �Լ�ó�� ��� ���� �ƴϸ� placeholders::_10�̿��ؼ� �Ű����� ���))
}

Groot::~Groot()
{
	delete weapon;
	delete leftHand;
}

void Groot::Update()
{
	ModelAnimator::Update();


	//leftHand->Update();

	if (KEY_DOWN('1'))
		PlayClip(0, speed, takeTime);

	if (KEY_DOWN('2'))
		PlayClip(1, speed, takeTime);

	if (KEY_DOWN('3'))
		PlayClip(2, speed, takeTime);

	UpdateLeftHand();

	Move();
}

void Groot::Render()
{
	ModelAnimator::Render();
	weapon->Render();
}

void Groot::Debug()
{
	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f, 1.0f);

	ModelAnimator::Debug();

	weapon->Debug();
}

void Groot::UpdateLeftHand()
{
	UINT nodeIndex = reader->GetNodeIndex("mixamorig:LeftHand");

	Matrix nodeTransform = GetTransformByNode(nodeIndex);

	leftHand->GetWorld() = nodeTransform * world;

	weapon->Update();
}

void Groot::SetClip(AnimState state)
{
	if (curState != state)
	{
		PlayClip(state);
		curState = state;
	}
}

void Groot::Move()
{
	if (!KEY_PRESS(VK_LBUTTON))
	{
		if (KEY_PRESS('W'))
		{
			rotation.y = Camera::GetInstance()->GetRotY();
			translation -= Forward() * moveSpeed * Time::Delta();
			SetClip(RUN);
		}

		if (KEY_PRESS('S'))
		{
			translation -= Backward() * moveSpeed * Time::Delta();
			SetClip(RUN);
		}
		if (KEY_UP('W') || KEY_UP('S'))
			SetClip(IDLE);

		if (KEY_PRESS('A'))
		{
			rotation.y -= rotSpeed * Time::Delta();
		}
		if (KEY_PRESS('D'))
		{
			rotation.y += rotSpeed * Time::Delta();
		}

		if (KEY_DOWN(VK_LBUTTON))
		{
			SetClip(ATTACK);
		}
	}
}
