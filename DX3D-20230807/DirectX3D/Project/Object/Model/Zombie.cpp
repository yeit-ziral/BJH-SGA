#include "Framework.h"
#include "Zombie.h"

Zombie::Zombie()
	: ModelAnimator("Zombie")
{
	scale *= 0.35f;
	ReadClip("Happy Idle");
	ReadClip("Throw");
	ReadClip("Walking");
	CreateTexture();

	reader->GetMaterial()[0]->Load(L"Zombie.mat");

	weapon = new Knife_A();
	weapon->scale *= 100.0f;

	leftHand = new Transform();

	weapon->SetParent(leftHand);
}

Zombie::~Zombie()
{
	delete weapon;
	delete leftHand;
}

void Zombie::Update()
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
}

void Zombie::Render()
{
	ModelAnimator::Render();
	weapon->Render();
}

void Zombie::Debug()
{
	ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
	ImGui::SliderFloat("TakeTime", &takeTime, 0.0f, 1.0f);

	ModelAnimator::Debug();

	weapon->Debug();
}

void Zombie::UpdateLeftHand()
{
	UINT nodeIndex = reader->GetNodeIndex("mixamorig:LeftHand");

	Matrix nodeTransform = GetTransformByNode(nodeIndex);

	leftHand->GetWorld() = nodeTransform * world;

	weapon->Update();
}
