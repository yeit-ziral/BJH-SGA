#include "Framework.h"
#include "ModelInstancingScene.h"

ModelInstancingScene::ModelInstancingScene()
{
	model = new ModelAnimatorInstancing("Zombie");
	model->ReadClip("Happy Idle");
	model->ReadClip("Walking");
	model->ReadClip("Throw");

	model->GetReader()->GetMaterial()[0]->SetDiffuseMap(L"Model/Zombie/creature_Base_color.png");    	// �������� ������ ��� ��
	model->GetReader()->GetMaterial()[0]->SetNormalMap(L"Model/Zombie/creature_Base_color.png"); 	// �������� ������ ��� ��


	for (float z = 0; z < 10; z++) // ���� �� 100 �� ����
	{
		for (float x = 0; x < 10; x++)
		{
			Transform* transform = model->Add();

			transform->translation = { x * 10, 0, z * 10 };
			transform->scale *= 0.01f;
		}
	}
}

ModelInstancingScene::~ModelInstancingScene()
{
	delete model;
}

void ModelInstancingScene::Update()
{
	model->Update();
}

void ModelInstancingScene::PreRender()
{
}

void ModelInstancingScene::Render()
{
	model->Render();
}

void ModelInstancingScene::PostRender()
{
	ImGui::SliderInt("InstanceIndex", &instanceIndex, 0, 100);
	ImGui::SliderInt("ClipIndex", &clip, 0, 2); // ���� groot�� ������ �ִ� clip�� 3���ۿ� ����

	if (ImGui::Button("Play"))
		model->PlayClip(instanceIndex, clip);

	model->Debug();
}
