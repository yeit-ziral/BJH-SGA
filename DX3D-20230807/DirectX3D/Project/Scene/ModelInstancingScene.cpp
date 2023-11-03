#include "Framework.h"
#include "ModelInstancingScene.h"

ModelInstancingScene::ModelInstancingScene()
{
	model = new ModelAnimatorInstancing("Groot");
	model->ReadClip("Sad Idle");
	model->ReadClip("Drunk Run Forward");
	model->ReadClip("Mutant Swiping");

	model->GetReader()->GetMaterial()[0]->SetDiffuseMap(L"Model/Groot/groot_diffuse.png");    	// 수동으로 성정해 줘야 됨
	model->GetReader()->GetMaterial()[0]->SetNormalMap(L"Model/Groot/groot_normal_map.png"); 	// 수동으로 성정해 줘야 됨

	for (float z = 0; z < 10; z++) // 같은 모델 100 개 생성
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
	ImGui::SliderInt("ClipIndex", &clip, 0, 2); // 현재 groot가 가지고 있는 clip은 3개밖에 없음

	if (ImGui::Button("Play"))
		model->PlayClip(instanceIndex, clip);

	model->Debug();
}
